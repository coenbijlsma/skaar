/*
 * File: client_conn.h
*/

#ifndef CLIENT_CONN_H
#define CLIENT_CONN_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <netdb.h>

#define IRC_STANDARD_PORT 6667

class client_conn{
    int cc_fd;
    int cc_connected;
    struct sockaddr_in cc_addr;
    char* cc_host;
    int cc_port;
        
public:
    client_conn(char* host, int port);
    virtual ~client_conn();

    int fd();
    int connected();
    int create_conn();
    int destroy_conn();
    int send_message(char *msg);
    char* read_message();
};

#endif

