#include "mode_message.h"

mode_message::mode_message(char* msg, client* cl, char* chan, char* user, char* mod, char* lim, char* bmask) : message(msg, cl){
    //printf("mode_message::mode_message(%s, cl, %s, %s, %s, %s, %s\n", msg, chan, user, mod, lim, bmask);
    channel 	= chan;
    nick 	= user;
    mode 	= mod;
    limit 	= ( strcmp(lim, "0") == 0 ? 0 : lim);
    banmask 	= bmask;
    command	= "MODE";
}

mode_message::~mode_message(){}

char* mode_message::get_channel(){
    return channel;
}

char* mode_message::get_nick(){
    return nick;
}

char* mode_message::get_mode(){
    return mode;
}

char* mode_message::get_limit(){
    return limit;
}

char* mode_message::get_banmask(){
    return banmask;
}

char* mode_message::to_string(int rfc){
    int msglen;
    char* t_msg;
    
    if(channel != 0 && strlen(channel) > 0){
	msglen = strlen(command) + strlen(" ") + strlen(channel) + strlen(" ") + strlen(mode);
	if(limit != 0){ msglen += (strlen(" ") + strlen(limit)); }
	if(nick != 0){ msglen += (strlen(" ") + strlen(nick)); }
	if(banmask != 0){ msglen += (strlen(" ") + strlen(banmask)); }
	msglen += strlen(CRLF);
	
	t_msg = (char*)malloc(msglen +1);
	memset(t_msg, 0, msglen +1);
	strcpy(t_msg, command);
	strcat(t_msg, " ");
	strcat(t_msg, channel);
	strcat(t_msg, " ");
	strcat(t_msg, mode);
	if(limit != 0){ strcat(t_msg, " "); strcat(t_msg, limit); }
	if(nick != 0){ strcat(t_msg, " "); strcat(t_msg, nick); }
	if(banmask != 0){ strcat(t_msg, " "); strcat(t_msg, banmask); }
	strcat(t_msg, CRLF);
    }else{
	msglen = strlen(command) + strlen(" ") + strlen(nick) + strlen(" ") + strlen(mode) + strlen(CRLF);
	t_msg = (char*)malloc(msglen +1);
	strcpy(t_msg, command);
	strcat(t_msg, " ");
	strcat(t_msg, nick);
	strcat(t_msg, " ");
	strcat(t_msg, mode);
	strcat(t_msg, CRLF);
    }
    
    return t_msg;
}
