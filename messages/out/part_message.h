/*
4.2.2 Part message

Command: PART
Parameters: <channel>{,<channel>}

The PART message causes the client sending the message to be removed
from the list of active users for all given channels listed in the
parameter string.

Numeric Replies:
ERR_NEEDMOREPARAMS               ERR_NOSUCHCHANNEL
ERR_NOTONCHANNEL

Examples:
PART #twilight_zone              ; leave channel "#twilight_zone"
PART #oz-ops,&group5             ; leave both channels "&group5" and
                                   "#oz-ops".
*/

#ifndef PART_MESSAGE_H
#define PART_MESSAGE_H

#include "../message.h"

class part_message : message {
    char* channels;

public:
    part_message(char* msg, client* cl, char* channels);
    ~part_message();
    char* get_chans();
    char* to_string(int rfc);
};

#endif