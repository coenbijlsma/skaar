#include "pass_message.h"

pass_message::pass_message(char* msg, client* cl, char* passwd) : message(msg, cl){
    command = "PASS";
    password = passwd;
}

pass_message::~pass_message(){}

char* pass_message::to_string(int rfc){
	int msg_length = strlen(command) + strlen(" :") + strlen(password) + strlen(CRLF);

    char* tmp_str = (char*)malloc(msg_length +1);
    memset(tmp_str, 0, (msg_length +1));
    strcpy(tmp_str, command);
    strcat(tmp_str, " :");
    strcat(tmp_str, password);
    strcat(tmp_str, CRLF);
    return tmp_str;
}

