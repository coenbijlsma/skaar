#ifndef EXAMPLEUI_H
#define EXAMPLEUI_H

#include <stdio.h>
#include "virtualui.h"

class exampleui : public virtualui {

public:
    int print_msg(char* msg){
	printf(msg);
    }
    
    int print_err(char* error, char* msg){
	fprintf(stderr, error);
	fprintf(stderr, msg);
    }
};

#endif
