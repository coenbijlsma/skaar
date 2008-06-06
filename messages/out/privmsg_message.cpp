#include "privmsg_message.h"

privmsg_message::privmsg_message(char* msg, client* cl, char* recv, char* txt) : message(msg, cl){
    if(recv == 0 || strlen(recv) == 0){
	fprintf(stderr, "The message cannot be sent without receivers.\n");
    }
    if(txt == 0 || strlen(txt) == 0){
	fprintf(stderr, "The text cannot be empty.\n");
    }
    receivers = recv;
    text = txt;
    command = "PRIVMSG";
}

privmsg_message::~privmsg_message(){}

char* privmsg_message::get_receivers(){
    char* t_recv = (char*)malloc(strlen(receivers) +1);
    memset(t_recv, 0, strlen(receivers) +1);
    strcpy(t_recv, receivers);
    return t_recv;
}

char* privmsg_message::get_text(){
    char* t_text = (char*)malloc(strlen(text) +1);
    memset(t_text, 0, strlen(text) +1);
    strcpy(t_text, text);
    return t_text;
}

char* privmsg_message::to_string(int rfc){
    int msglen = strlen(command) 
		 + strlen(" ") 
		 + strlen(receivers) 
		 + strlen(" :") 
		 + strlen(text) 
		 + strlen(CRLF);
    
    char* t_msg = (char*)malloc(msglen +1);
    memset(t_msg, 0, msglen +1);
    strcpy(t_msg, command);
    strcat(t_msg, " ");
    strcat(t_msg, receivers);
    strcat(t_msg, " :");
    strcat(t_msg, text);
    strcat(t_msg, CRLF);
    return t_msg;
}

