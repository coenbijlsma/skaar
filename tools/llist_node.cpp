#include "llist_node.h"

llist_node::llist_node(void *value){
    _value = value;
}

llist_node::~llist_node(){}

int llist_node::set_child(llist_node *child){
    _child = child;
    return 0;
}

llist_node *llist_node::child(){
    return _child;
}

void *llist_node::value(){
    return _value;
}
