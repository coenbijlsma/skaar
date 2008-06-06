#include "message.h"
#include "out/pass_message.h"
#include "out/nick_message.h"
#include "out/user_message.h"
#include "out/oper_message.h"
#include "out/quit_message.h"
#include "out/join_message.h"
#include "out/mode_message.h"
#include "out/privmsg_message.h"
#include "../tools/stringtokenizer.h"

message::message(char* msg, client* cl){
    raw = msg;
    clnt = cl;
}

message::~message(){}

char* message::to_string(int rfc){
    return raw;
}

int message::set_raw_no_command(){
    if(raw == 0 || strlen(raw) == 0){
		return 1;
    }

    raw_no_command = strchr(raw, SPACE) +1;
    
    if(raw_no_command == 0){
		return 1;
    }
    return 0;
}

message* message::to_message(char* msg, client* cl){
    //printf("message::to_message(%s)\n",msg);

    if( msg[0] == '/'){
        char* sp_loc = strchr(msg, SPACE);
        char* t_command;
        message* tmp_msg;
	stringtokenizer* st = new stringtokenizer(msg, ' ');
        //printf("sp_loc == \"%s\", t_command == %s\n",sp_loc, t_command);

        /// Figure out the command
        if(sp_loc == 0){
            // If there is no space, then t_command = msg
            t_command = (char*)malloc(strlen(msg) -1);
            memset(t_command, 0, strlen(msg) -1);
            t_command = strncpy(t_command, msg +1, strlen(msg) -1);
        }else{
            t_command = (char*)malloc((sp_loc - msg));
            memset(t_command, 0, (sp_loc -msg));
            t_command = strncpy(t_command, msg +1, (sp_loc - msg) -1);
        }
	
	// ALIASES
	if(strcmp(t_command, "exit") == 0){
	    t_command = (char*)malloc(strlen("quit") +1);
	    memset(t_command, 0, strlen("quit") +1);
	    strcpy(t_command, "quit");
        }
	
        char* cmd_end = t_command + strlen(t_command);
        cmd_end = '\0';

        // Start handling the messages
	
	// PASS
        if(strcmp(t_command, "pass") == 0){
            pass_message* pass_msg = new pass_message(msg, cl, (sp_loc +1));
            tmp_msg = (message*)pass_msg;
	
	// NICK    
        }else if(strcmp(t_command, "nick") == 0){
	    char* t_nick = (msg + strlen("/nick "));
			
	    nick_message* nick_msg = new nick_message(msg, cl, t_nick);
	    tmp_msg = (message*)nick_msg;
	    
	// USER    
	}else if(strcmp(t_command, "user") == 0){
	    if(st->cnttok() != 5){
		fprintf(stderr, "Illegal format for USER message \"%s\"\n", msg);
		return 0;
	    }
	    st->next(); // discard the command
	    user_message* user_msg = new user_message(msg, cl, st->next(), st->next(), st->next(), st->next());
	    tmp_msg = (message*)user_msg;
	// OPER
	}else if(strcmp(t_command, "oper") == 0){
	    //st = new stringtokenizer(msg, ' ');
	    if(st->cnttok() != 3){
		fprintf(stderr, "Illegal format for OPER message \"%s\"\n", msg);
		return 0;
	    }
	    st->next(); // discard the command
	    oper_message* oper_msg = new oper_message(msg, cl, st->next(), st->next());
	    tmp_msg = (message*)oper_msg;
	
	// QUIT
	}else if(strcmp(t_command, "quit") == 0){
	    char* cquit_msg = (msg + strlen(t_command) + 2);
	    quit_message* quit_msg = new quit_message(msg, cl, cquit_msg);
	    tmp_msg = (message*)quit_msg;
	
	// JOIN
	}else if(strcmp(t_command, "join") == 0){
	    if(st->cnttok() > 3){
		fprintf(stderr, "Illegal format for JOIN message \"%s\"\n", msg);
		return 0;
	    }
	    st->next(); // discard the command
	    join_message* join_msg = new join_message(msg, cl, st->next(), st->next());
	    tmp_msg = (message*)join_msg;
	
	// MODE
	}else if(strcmp(t_command, "mode") == 0){
	    if(st->cnttok() < 3){
		fprintf(stderr, "Illegal format for MODE message \"%s\"\n", msg);
		return 0;
	    }
	    st->next(); // discard the command
	    char* t_tok = st->next();
	    char* t_mode = st->next();
	    if(t_tok[0] == '#' || t_tok[0] == '&'){ // channel MODE
		char* t_limit = st->next();
		char* t_user = st->next();
		char* t_banmask = st->next();
	    	mode_message* mode_msg = new mode_message(msg, cl, t_tok, t_user, t_mode, t_limit, t_banmask);
		tmp_msg = (message*)mode_msg;
	    }else{ // user MODE
		mode_message* mode_msg = new mode_message(msg, cl, 0, t_tok, t_mode, 0, 0);
		tmp_msg = (message*)mode_msg;
	    }
	
	// PRIVMSG
	}else if(strcmp(t_command, "say") == 0){
	    st->next(); // discard the command
	    if( ! st->has_next()){
		// Prevent a SEGFAULT and return NULL
		tmp_msg = (message*)0;
	    }else{
		char* t_recv = st->next();
		char* t_txt = (msg + strlen("/say ") + strlen(t_recv) +1);
		privmsg_message* privmsg_msg = new privmsg_message(msg, cl, t_recv, t_txt);
		tmp_msg = (message*)privmsg_msg;
	    }
	}else{
	    //tmp_msg = new message(msg, cl);    
	    // illegal message
	    tmp_msg = (message*)0;
	}

    	return tmp_msg;
    }else{
    	return new message(msg, cl);
    }

    return 0;
}
