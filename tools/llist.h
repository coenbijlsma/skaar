#ifndef LLIST_H
#define LLIST_H

#include "llist_node.h"

class llist {
    llist_node *_root;
    
public:
    llist();
    ~llist();
    
    int add(llist_node *parent, llist_node *node);
    int remove(llist_node *node);
    llist_node *root();
    
};

#endif
