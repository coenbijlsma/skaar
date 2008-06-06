#ifndef LLIST_NODE_H
#define LLIST_NODE_H

class llist_node {
    llist_node *_child;
    void *_value;
    
public:
    llist_node(void *value);
    ~llist_node();
    
    int set_child(llist_node *child);
    llist_node *child();
    void *value();
};

#endif
