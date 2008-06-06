/*
 * File: client.h
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "virtualui.h" // to print the messages
#include "client_conn.h" // to connect to the server
#include "messages/message.h" // to send messages to the server

#define LINE_MAXLEN 1000
#define CLIENT_CONF "client.conf"

class client_conn;
class message;

class client{
    client_conn* conn;
    char* user_name;
    char* nick;
    char* prev_nick;
    char* password;
    char* host;
    char* chans;
    int port;
    int auto_connect;
    int ajoin;
    
    // Needed to print messages
    virtualui* ui;    
    
    // Reads the file client.conf
    int read_config();
	
    // handles a config line
    int hcline(char* line);
    
public:
    client(char* u_name, char* u_nick, char* u_password, char* u_host, int u_port, int auto_conn);
    virtual ~client();
    
    /*
    */
    int register_ui(virtualui* vui);
    
    int send_message(message* msg);

    /*
     * Connects this client to the desired channel. This basically means that 
     * the following three commands are sent to the server:
     * - USER
     * - NICK
     * - PASS
    */
    int connect();

    void start_work();
    char* get_nick();
    char* get_pnick();
    int is_command(char* line);
	
    /*
     * THIS METHOD DOES NOT CAUSE A NICKCHANGE!
     * Changes the nick of the client internally.
    */
    int change_nick(char* new_nick);
    
};

#endif
