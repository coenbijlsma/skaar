#include "client_conn.h"

client_conn::client_conn(char* host, int port){
    //printf("client_conn(%s, %d)\n", host, port);
    
    if(port == 0){
	cc_port = IRC_STANDARD_PORT;
    }else{
	cc_port = port;
    }
    
    struct hostent *h = gethostbyname(host);
    
    if(h == 0){
	herror("gethostbyname");
	cc_host = host;
    }else{    
	cc_host = inet_ntoa(*((struct in_addr*)h->h_addr));
    }
    cc_connected = 0;
}

client_conn::~client_conn(){
    if(cc_connected == 1){
	    if(shutdown(cc_fd, SHUT_RDWR) == -1){
	        perror("shutdown");
	    }else{
	        cc_connected = 0;
	        if(close(cc_fd) == -1){
        		perror("close");
	        }
	    }
    }
}

int client_conn::fd(){
    return cc_fd;
}

int client_conn::connected(){
    return cc_connected;
}

int client_conn::create_conn(){
    if( (cc_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    	perror("socket");
    	return 1;
    }
    
    memset(&cc_addr, 0, sizeof(cc_addr));
    cc_addr.sin_family		= AF_INET;
    cc_addr.sin_port		= htons(cc_port);
    cc_addr.sin_addr.s_addr	= inet_addr(cc_host);
    
    if(connect(cc_fd, (struct sockaddr *)&cc_addr, sizeof(cc_addr)) == -1){
    	close(cc_fd);
    	perror("connect");
    	return 1;
    }
    
    printf("Connected to %s:%d\n",cc_host, cc_port);
    cc_connected = 1;
    return 0;
}

int client_conn::destroy_conn(){
    if(cc_connected == 0){
        printf("Only fools disconnect while not connected.\n");
    	return 1;
    }

    if(shutdown(cc_fd, SHUT_RDWR) == -1){
        perror("shutdown");
        return 1;
    }

    cc_connected = 0;
    if(close(cc_fd) == -1){
        perror("close");
    	return 1;
    }

    printf("You are now disconnected.\n");
    return 0;
}

int client_conn::send_message(char *msg){
    if(cc_connected == 0){
	create_conn();
    }
    
    int bytes_sent;
    
    if(msg[strlen(msg)] != '\0'){
		msg[strlen(msg)] = '\0';
    }
    
    //printf("Trying to send message %s\n", msg);
    if( (bytes_sent = send(cc_fd, msg, strlen(msg), 0)) == -1 || bytes_sent != strlen(msg) ){
    	perror("send");
    	return 1;
    }

    return 0;
}

char* client_conn::read_message(){
    if(cc_connected == 0){
	fprintf(stderr, "Not connected\n");
	return 0;
    }
    
    char* t_msg = (char*)malloc(513);
    int msglen;
    memset(t_msg, 0, 513);
        
    //printf("waiting for message from fd %d...\n",cc_fd);
    while(strlen(t_msg) <= 512){
	char* c = (char*)malloc(513);
	memset(c, 0, 513);
	
	switch(recv(cc_fd, c, 512, 0)){
	    case 0:
		return 0;
	    case -1:
		perror("recv");
		return 0;
	    default:
		strcat(t_msg, c);
	}
	msglen = strlen(t_msg);
	//printf("Incoming: %s\n", t_msg);
	break;
	//if(msglen >= 2 && strcmp( (t_msg + (msglen -1)    
    }
    return t_msg;
}
