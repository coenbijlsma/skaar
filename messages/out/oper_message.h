/*
4.1.5 Oper
Command: 	OPER
Parameters: 	<user> <password>

OPER message is used by a normal user to obtain operator privileges. 
The combination of <user> and <password> are required to gain Operator privileges.
If the client sending the OPER command supplies the correct password for the given user, 
the server then informs the rest of the network of the new operator by issuing a "MODE +o" 
for the clients nickname. The OPER message is client-server only.

Numeric Replies:
ERR_NEEDMOREPARAMS 	RPL_YOUREOPER
ERR_NOOPERHOST 	ERR_PASSWDMISMATCH

Example:

OPER foo bar          ; Attempt to register as an operator
                      using a username of "foo" and "bar" as
                                            the password.
*/

#ifndef OPER_MESSAGE_H
#define OPER_MESSAGE_H

#include "../message.h"

class oper_message : public message {
    char* user;
    char* password;

public:
    oper_message(char* msg, client* cl, char* uname, char* pwd);
    ~oper_message();
    char* get_uname();
    char* get_pwd();
    char* to_string(int rfc);
    
};

#endif
