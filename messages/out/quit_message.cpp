#include "quit_message.h"

quit_message::quit_message(char* msg, client* cl, char* qm) : message(msg, cl) {
    qmsg = qm;
    command = "QUIT";
}

quit_message::~quit_message(){}

char* quit_message::get_qmsg(){
    return qmsg;
}

char* quit_message::to_string(int rfc){
    int msglen;
    char* t_msg;
    
    msglen = strlen(command);
    
    if(qmsg != 0 && strlen(qmsg) > 0){
	msglen += (strlen(" :") + strlen(qmsg));
    }else{
	msglen += strlen(" ");
	msglen += strlen(clnt->get_nick());
    }
    msglen += strlen(CRLF);
    
    t_msg = (char*)malloc(msglen +1);
    memset(t_msg, 0, msglen +1);
    strcpy(t_msg, command);
    if(qmsg != 0 && strlen(qmsg) > 0){
	strcat(t_msg, " :");
	strcat(t_msg, qmsg);
    }else{
	strcat(t_msg, " ");
	strcat(t_msg, clnt->get_nick());
    }
    strcat(t_msg, CRLF);
    
    return t_msg;
}
