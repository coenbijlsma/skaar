/*
4.1.3 User message

      Command: USER
   Parameters: <username> <hostname> <servername> <realname>

   The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of s new user.  It is
   also used in communication between servers to indicate new user
   arriving on IRC, since only after both USER and NICK have been
   received from a client does a user become registered.

   Between servers USER must to be prefixed with client's NICKname.
   Note that hostname and servername are normally ignored by the IRC
   server when the USER command comes from a directly connected client
   (for security reasons), but they are used in server to server
   communication.  This means that a NICK must always be sent to a
   remote server when a new user is being introduced to the rest of the
   network before the accompanying USER is sent.

   It must be noted that realname parameter must be the last parameter,
   because it may contain space characters and must be prefixed with a
   colon (':') to make sure this is recognised as such.

   Since it is easy for a client to lie about its username by relying
   solely on the USER message, the use of an "Identity Server" is
   recommended.  If the host which a user connects from has such a
   server enabled the username is set to that as in the reply from the
   "Identity Server".

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Examples:

   USER guest tolmoon tolsun :Ronnie Reagan

                                   ; User registering themselves with a
                                   username of "guest" and real name
                                   "Ronnie Reagan".

   :testnick USER guest tolmoon tolsun :Ronnie Reagan
                                   ; message between servers with the
                                   nickname for which the USER command
                                   belongs to
*/

#ifndef USER_MESSAGE_H
#define USER_MESSAGE_H

#include "../message.h"

class user_message : public message {
	char* username;
	char* hostname;
	char* servername;
	char* realname;

public:
	user_message(char* msg, client* cl, char* uname, char* hname, char* sname, char* rname);
	virtual ~user_message();

	char* get_uname();
	char* get_hname();
	char* get_sname();
	char* get_rname();
	
	char* to_string(int rfc);
};

#endif

