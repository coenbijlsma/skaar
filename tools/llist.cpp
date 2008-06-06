#include <stdio.h>

#include "llist.h"

llist::llist(){}
llist::~llist(){}

int llist::add(llist_node *parent, llist_node *node){
    if(parent == 0){
	// We want to set the root node
	if(_root != 0){
	    fprintf(stderr, "The root node cannot be replaced!\n");
	    return 1;
	}else{
	    _root = node;
	}
    }else{
	// Add a new node to an existing one
	if(parent->child() != 0){
	    // Replace the child
	    llist_node *tmp_chld = parent->child();
	    node->set_child(tmp_chld);
	}
	
	parent->set_child(node);
    }
    return 0;
}

int llist::remove(llist_node *node){
    if(node == 0){
	fprintf(stderr, "Node cannot be NULL!\n");
	return 1;
    }
    if(node == _root){
	_root = node->child();
	node = (llist_node *)0;
	return 0;
    }else{
    
	llist_node *parent = _root;
    
	// Search the parent of node    
	while(parent->child() != node && parent->child() != 0){
	    parent = parent->child();
        }

	if(parent->child() != node){
	    fprintf(stderr, "Node not in list!\n");
	    return 1;
	}
	
	llist_node *tmp_chld = node->child();
    
	// Tie the parent and the child together
	parent->set_child(tmp_chld);
	node = (llist_node *)0;
        return 0;
    }
}

llist_node *llist::root(){
    return _root;
}
