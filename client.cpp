#include <limits.h>
#include <signal.h>
#include <unistd.h>

#include "client.h"

client::client(char* u_name, char* u_nick, char* u_password, char* u_host, int u_port, int auto_conn){
    user_name	= u_name;
    nick	= u_nick;
    password	= u_password;
    host 	= u_host;
    port	= u_port;
    auto_connect = auto_conn;
    
    read_config();
    
    conn	= new client_conn(host, port);
    
    if(auto_connect != 0){
	if(connect() != 0){
	    exit(1);
	}
    }    
}

client::~client(){}

int client::register_ui(virtualui* vui){
    if(ui == 0){
	ui = vui;
	return 0;
    }else{
	fprintf(stderr, "client::register_ui --> UI already set.\n");
	return 1;
    }
}

//PRIV
int client::read_config(){
	FILE *fp = fopen(CLIENT_CONF, "r");
	char line[LINE_MAX];

	if(fp == 0){
		perror("reading config");
		return 1;
	}

	while(fgets(line, LINE_MAX, fp) != 0){
		if(hcline(line) != 0){
			fprintf(stderr, "Invalid config line: %s\n",line);
		}
	}

	if(fclose(fp) == EOF){
		perror("closing file");
	}
	return 0;
}

//PRIV
int client::hcline(char* line){
	char* param;
	char* value;

	value = strchr(line, '=') +1;
	value[strlen(value) -1] = '\0';
	param = (char*) malloc(value - line);
	memset(param, 0, (value - line));
	param = strncpy(param, line, (value - line) -1);
	//printf("param: %s\n",param);
	//printf("value: %s\n",value);

	if(strcmp(param, "name") == 0){
	    user_name = (char*)malloc(strlen(value));
	    user_name = strcpy(user_name, value);

	}else if(strcmp(param, "nick") == 0){
	    nick = (char*)malloc(strlen(value));
	    nick = strcpy(nick, value);

	}else if(strcmp(param, "password") == 0){
	    password = (char*)malloc(strlen(value));
	    password = strcpy(password, value);
	    
	}else if(strcmp(param, "auto_connect") == 0){
	    memset(&auto_connect, 0, sizeof(int));
	    //printf("%d\n",atoi(value));
	    auto_connect = atoi(value);
	}else if(strcmp(param, "host") == 0){
	    host = (char*)malloc(strlen(value) +1);
	    memset(host, 0, strlen(value) +1);
	    strcpy(host, value);
	}else if(strcmp(param, "channels") == 0){
	    chans = (char*)malloc(strlen(value) +1);
	    memset(chans, 0, strlen(value) +1);
	    strcpy(chans, value);	    
	}else if(strcmp(param, "auto_join") == 0){
	    ajoin = atoi(value);
	}else{
		fprintf(stderr, "Invalid parameter: %s\n", param);
	}

	return 0;
}

void client::start_work(){
    char line[LINE_MAX];
    memset(&line, 0, LINE_MAX);
    message* msg;
    message* smsg;
    
    pid_t pid = fork();
    
    if(pid == 0){
	//printf("PID == %d\n",getpid());
	while(conn->connected() == 1){
	    char* sline = conn->read_message();
	    smsg = message::to_message(sline, this);
	    
	    // Print the message to the alternate ui, if it's set
	    if(ui != 0){
		ui->print_msg(smsg->to_string(RFC_1459));
	    }else{
		printf("%s",smsg->to_string(RFC_1459));
	    }
	}
    }else if(pid < 0){
	perror("fork");
	exit(1);
    }else{
	while( (strcmp(line, "/exit") != 0) ){
	    memset(&line, 0, LINE_MAX);
	    char c;

	    for(int i = 0; (c = getchar()) != '\n' && i < LINE_MAX; i++){
		line[i]  = c;
	    }

	    if(line[0] != '/'){
		/*
		 * The message does not start with a slash,
		 * so the message is a PRIVMSG to the active channel
		 * the client is in.
		*/
		char __buf[LINE_MAX] = "/say ";
		strcat(__buf, line);
		memset(&line, 0, LINE_MAX);
		strcpy(line, __buf);
	    }

	    msg = message::to_message(line, this);
	    if(msg == (message*)0){
		if(is_command(line) == 1){
		    // handle the command
		}else{
		    // Print the message to the alternate ui, if it's set
		    if(ui != 0){
			ui->print_err("Invalid message: ", line);
		    }else{
			fprintf(stderr, "Invalid message: %s\n", line);
		    }
		}
	    }else{    
		send_message(msg);	
	    }
	} // while
	
	if(conn->connected() == 1){
	    conn->destroy_conn();
	}
	kill(pid, 2); // kill the child
	//exit(0);
    }
}

int client::send_message(message* msg){
    if(msg == 0){
        return 1;
    }

    if(conn->connected() != 1){
	    if(conn->create_conn() == 1){
	        return 1;
	    }
    }
    char* c_msg = msg->to_string(RFC_1459);
    
    return conn->send_message(c_msg);
}

int client::connect(){
	int pm_length = strlen("/pass ") + strlen(password);
	int nm_length = strlen("/nick ") + strlen(nick);
	int um_length = strlen("/user ") + strlen(nick) + strlen(" ") 
					+ strlen("localhost ") + strlen("blaat ") 
					+ strlen(user_name) ;

	char* pm = (char*)malloc(pm_length +1);
	char* nm = (char*)malloc(nm_length +1);
	char* um = (char*)malloc(um_length +1);
	
	memset(pm, 0, pm_length +1);
	strcpy(pm, "/pass ");
	strcat(pm, password);
	message* pmessage = message::to_message(pm, this);
	if(send_message(pmessage) != 0){
		// Print the message to the alternate ui, if it's set
		if(ui != 0){
		    ui->print_err("ERROR: Sending PASS message failed!\n", "");
		}else{
		    fprintf(stderr, "ERROR: Sending PASS message failed!\n");
		}
		return 1;
	}

	memset(nm, 0, nm_length +1);
	strcpy(nm, "/nick ");
	strcat(nm, nick);
	message* nmessage = message::to_message(nm, this);
	if(send_message(nmessage) != 0){
		if(ui != 0){
		    ui->print_err("ERROR: Sending NICK message failed!\n", "");
		}else{
		    fprintf(stderr, "ERROR: Sending NICK message failed!\n");
		}
		return 1;
	}

	memset(um, 0, um_length +1);
	strcpy(um, "/user ");
	strcat(um, nick);
	strcat(um, " ");
	strcat(um, "localhost ");
	strcat(um, "blaat ");
	strcat(um, user_name);
	message* umessage = message::to_message(um, this);
	if(send_message(umessage) != 0){
	    if(ui != 0){
		ui->print_err("ERROR: Sending USER message failed!\n", "");
	    }else{
		fprintf(stderr, "ERROR: Sending USER message failed!\n");
	    }
		return 1;
	}
	
	if(ajoin == 1){
	    if(chans != 0){
		int ml = strlen("JOIN ") + strlen(chans) + strlen("\r\n") + 1;
		char* jm = (char*)malloc(ml);
		memset(jm, 0, ml);
		strcpy(jm, "JOIN ");
		strcat(jm, chans);
		strcat(jm, "\r\n");
		conn->send_message(jm);
	    }else{
		if(ui != 0){
		    ui->print_err("No channels to join!\n", "");
		}else{
		    fprintf(stderr, "No channels to join!\n");
		}
		return  1;
	    }
	}
	return 0;
}

char* client::get_nick(){
	return nick;
}

char* client::get_pnick(){
	return prev_nick;
}

int client::change_nick(char* new_nick){
	// This is only neccesary if the nick is changed 
	// instead of set for the first time.
	if(nick != 0){
		if(prev_nick != 0){
			free(prev_nick);
		}
	
		prev_nick = (char*)malloc(strlen(nick) +1);
		memset(prev_nick, 0, strlen(nick) +1);
		strcpy(prev_nick, nick);
	}
	
	nick = (char*)malloc(strlen(new_nick) +1);
	memset(nick, 0, strlen(new_nick) +1);
	strcpy(nick, new_nick);
	return 0;
}

int client::is_command(char* line){
    return 0;
}
