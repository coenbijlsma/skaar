#ifndef EXAMPLEUI_H
#define EXAMPLEUI_H

//#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "virtualui.h"

class exampleui : public virtualui {

public:
    
    exampleui(){
	initscr();
	cbreak();
	noecho();
    }
    
    ~exampleui(){
	endwin();
    }
    
    int print_msg(char* msg){
	//printf(msg);
	printw(msg);
	refresh();
	return 0;
    }
    
    int print_err(char* error, char* msg){
	printw(error);
	printw(msg);
	refresh();
	//fprintf(stderr, error);
	//fprintf(stderr, msg);
	return 0;
    }
};

#endif
