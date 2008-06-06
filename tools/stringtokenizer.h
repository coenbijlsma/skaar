#ifndef STRINGTOKENIZER_H
#define STRINGTOKENIZER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class stringtokenizer {
    char* sequence;
    char delimeter;
    int cloc;
    char* ctok;
    char* ntok;
    
public:
    stringtokenizer(char* seq, char delim);
    ~stringtokenizer();
    
    int has_next();
    int cnttok();
    char* next();
};

#endif
