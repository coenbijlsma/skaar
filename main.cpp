#include "client.h"

void display_help(void);

int main(int argc, char **argv){
    client* cl = 0;
    //printf("%d\n", argc);
    
    if(argc == 1){
	cl = new client(0, 0, 0, 0, 0, 0);
    }else if(argc == 5){
	cl = new client(argv[1], argv[2], argv[3], argv[4], 0, 0);
    }else if(argc == 6){
	cl = new client(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), 0);
    }else if(argc == 7){
	cl = new client(argv[1], argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6]));
    }else{
	display_help();
	return 1;
    }
    
    cl->start_work();
    //message::to_message("Blaat");
    return 0;
}

void display_help(void){
    printf("Usage:\nclient [<username> <nick> <password> <host> [<port> [auto_connect]] ]\n");
}
