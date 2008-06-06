#include "client.h"

#define CHAN_LOCAL 		'&'
#define CHAN_DISTRUBUTED 	'#'

class channel {
    char* name;
    char type;
    
public:
    channel(char* c_name, char c_type);
    virtual ~channel();
    char get_type();
    char* get_name();
};

