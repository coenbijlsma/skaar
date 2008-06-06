#ifndef VIRTUALUI_H
#define VIRTUALUI_H

class virtualui {
    
public:
    virtual int print_msg(char* msg) =0;
    virtual int print_err(char* error, char* msg) =0;
};

#endif
