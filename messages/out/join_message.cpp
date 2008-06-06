#include "join_message.h"

join_message::join_message(char* msg, client* cl, char* chans, char* ckeys) : message(msg, cl) {
    if(chans == 0 || strlen(chans) == 0){
	fprintf(stderr, "You have to join at least one channel\n");
    }
    
    command = "JOIN";
    channels = chans;
    keys = ckeys;
}

join_message::~join_message(){}

char* join_message::get_channels(){
    return channels;
}

char* join_message::get_keys(){
    return keys;
}

char* join_message::to_string(int rfc){
    char* t_msg;
    int msglen = strlen(command) + strlen(" ") + strlen(channels);
    if(keys != 0 && strlen(keys) > 0){
	msglen += strlen(" ");
	msglen += strlen(keys);
    }
    msglen += strlen(CRLF);
    
    t_msg = (char*)malloc(msglen +1);
    memset(t_msg, 0, msglen +1);
    strcpy(t_msg, command);
    strcat(t_msg, " ");
    strcat(t_msg, channels);
    if(keys != 0 && strlen(keys) > 0){
	strcat(t_msg, " ");
	strcat(t_msg, keys);
    }
    strcat(t_msg, CRLF);
    return t_msg;
}

