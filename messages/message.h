/*
THE PSEUDO FORMAT FOR A MESSAGE
<message> ::=
    [':' <prefix> <SPACE> ] <command> <params> <crlf>
<prefix> ::=
    <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command> ::=
    <letter> { <letter> } | <number> <number> <number>
<SPACE> ::=
    ' ' { ' ' }
<params> ::=
    <SPACE> [ ':' <trailing> | <middle> <params> ]
<middle> ::=
    <Any *non-empty* sequence of octets not including SPACE or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::=
    <Any, possibly *empty*, sequence of octets not including NUL or CR or LF>
<crlf> ::=
    CR LF

NOTES:

   1. <SPACE> is consists only of SPACE character(s) (0x20). Specially notice 
      that TABULATION, and all other control characters are considered 
      NON-WHITE-SPACE.
   2. After extracting the parameter list, all parameters are equal, whether 
      matched by <middle> or <trailing>. <Trailing> is just a syntactic trick to
      allow SPACE within parameter.
   3. The fact that CR and LF cannot appear in parameter strings is just artifact
      of the message framing. This might change later.
   4. The NUL character is not special in message framing, and basically could
      end up inside a parameter, but as it would cause extra complexities in
      normal C string handling. Therefore NUL is not allowed within messages.
   5. The last parameter may be an empty string.
   6. Use of the extended prefix (['!' <user> ] ['@' <host> ]) must not be
      used in server to server communications and is only intended for server to
      client messages in order to provide clients with more useful information
      about who a message is from without the need for additional queries.
*/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <string.h>

#include "../client.h"

#define SPACE ' '
#define CRLF "\n\r"
#define RFC_1459 0
#define RFC_2812 1
#define MSG_PREFIX ':'

class client;

class message {
    int set_raw_no_command(); 

protected:
    client* clnt;
    char*   raw;
    char*   command;
    char*   friendly_command;
    char*   prefix;
    char*   params;
    char*   raw_no_command;

public:
    message(char* msg, client* cl);
    virtual ~message();

    /*
     * Converts this message to a char-array,
     * compliant to the given rfc (must be
     * one of 1459, 2812).
    */
    virtual char* to_string(int rfc);

    /*
     * Translates the given char* to a decent message
     * for client cl. A message must always start with the command,
     * optionally followed by params, like the examply below:
     * /say Hello, world!
     * On success, this method returns a correctly set up message,
     * ready to send to the server. 
     * On failure, this method returns NULL.
    */
    static message* to_message(char* msg, client* cl);
};

#endif

