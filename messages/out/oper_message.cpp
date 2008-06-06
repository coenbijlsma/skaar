#include "oper_message.h"

oper_message::oper_message(char* msg, client* cl, char* uname, char* pwd) : message(msg, cl) {
    if(uname == 0 || strlen(uname) == 0){
	fprintf(stderr, "The name cannot be NULL\n");
	return;
    }
    if(pwd == 0 || strlen(pwd) == 0){
	fprintf(stderr, "The password cannot be NULL\n");
	return;
    }
    
    user = uname;
    password = pwd;
    command = "OPER";
}

oper_message::~oper_message(){}

char* oper_message::get_uname(){
    return user;
}

char* oper_message::get_pwd(){
    return password;
}

char* oper_message::to_string(int rfc){
    int msglen = strlen(command) + strlen(" ") + strlen(user) + strlen(" ") + strlen(password) + strlen(CRLF);
    char* t_msg = (char*)malloc(msglen + 1);
    memset(t_msg, 0, msglen +1);
    strcpy(t_msg, command);
    strcat(t_msg, " ");
    strcat(t_msg, user);
    strcat(t_msg, " ");
    strcat(t_msg, password);
    strcat(t_msg, CRLF);
    
    return t_msg;
}
