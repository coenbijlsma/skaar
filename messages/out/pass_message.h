/*
4.1.1 Password message

      Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   password can and must be set before any attempt to register the
   connection is made.  Currently this requires that clients send a PASS
   command before sending the NICK/USER combination and servers *must*
   send a PASS command before any SERVER command.  The password supplied
   must match the one contained in the C/N lines (for servers) or I
   lines (for clients).  It is possible to send multiple PASS commands
   before registering but only the last one sent is used for
   verification and it may not be changed once registered.  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere
*/

#ifndef PASS_MESSAGE_H
#define PASS_MESSAGE_H

#include "../message.h"

class pass_message : public message {
    char* password;

public:
    pass_message(char* msg, client* cl, char* passwd);
    virtual ~pass_message();
    char* to_string(int rfc);
};

#endif

