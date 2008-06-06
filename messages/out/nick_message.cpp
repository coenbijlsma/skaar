#include "nick_message.h"

nick_message::nick_message(char* msg, client* cl, char* nick) : message(msg, cl){
	command = "NICK";
	nickname = nick;
}

nick_message::~nick_message(){}

int nick_message::set_hopcount(unsigned hc){
	hopcount = hc;
	return 0;
}

char* nick_message::get_nick(){
	return nickname;
}

unsigned nick_message::get_hopcount(){
	return hopcount;
}

char* nick_message::to_string(int rfc){
	if(nickname == 0 || strlen(nickname) == 0){
		fprintf(stderr, "Illegal nick\n");
		return 0;
	}

	char* tmp_msg;
	int msg_length;

	if(clnt->get_nick() == 0 || strcmp(clnt->get_nick(), nickname) == 0){
		msg_length = strlen(command) + strlen(" ") + strlen(nickname) + strlen(CRLF);
		tmp_msg = (char*)malloc(msg_length +1);
		memset(tmp_msg, 0, msg_length +1);

		strcpy(tmp_msg, command);
		strcat(tmp_msg, " ");
		strcat(tmp_msg, nickname);
		strcat(tmp_msg, CRLF);
	}else{
		//chance the clients nick
		clnt->change_nick(nickname);

		msg_length = strlen(":") + strlen(clnt->get_pnick()) + strlen(" ") + strlen(command) + strlen(" ") + strlen(clnt->get_nick()) + strlen(CRLF);
		tmp_msg = (char*)malloc(msg_length +1);
		memset(tmp_msg, 0, msg_length +1);

		strcpy(tmp_msg, ":");
		strcat(tmp_msg, clnt->get_pnick());
		strcat(tmp_msg, " ");
		strcat(tmp_msg, command);
		strcat(tmp_msg, " ");
		strcat(tmp_msg, clnt->get_nick());
		strcat(tmp_msg, CRLF);
	}

	return tmp_msg;
}

