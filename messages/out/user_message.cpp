#include "user_message.h"

user_message::user_message(char* msg, client* cl, char* uname, char* hname, char* sname, char* rname) : message(msg, cl) {
	command = "USER";
	username = uname;
	hostname = hname;
	servername = sname;
	realname = rname;
}

user_message::~user_message(){}

char* user_message::get_uname(){
	return username;
}

char* user_message::get_hname(){
	return hostname;
}

char* user_message::get_sname(){
	return servername;
}

char* user_message::get_rname(){
	return realname;
}

char* user_message::to_string(int rfc){
	int msg_length = strlen(command) + strlen(" ") + strlen(username) 
					+ strlen(" ") + strlen(hostname) + strlen(" ") 
					+ strlen(servername) + strlen(" :") + strlen(realname) 
					+ strlen(CRLF);

	char* tmp_msg = (char*)malloc(msg_length +1);
	memset(tmp_msg, 0, msg_length +1);

	strcpy(tmp_msg, command);
	strcat(tmp_msg, " ");
	strcat(tmp_msg, username);
	strcat(tmp_msg, " ");
	strcat(tmp_msg, hostname);
	strcat(tmp_msg, " ");
	strcat(tmp_msg, servername);
	strcat(tmp_msg, " :");
	strcat(tmp_msg, realname);
	strcat(tmp_msg, CRLF);

	return tmp_msg;
}

