#include <stdio.h>

#include "llist.h"

int main(int argc, char** argv){
    llist *ll = new llist();
    llist_node *lln0 = new llist_node((void *)"Een");
    llist_node *lln1 = new llist_node((void *)"Twee");
    llist_node *lln2 = new llist_node((void *)"Drie");
    llist_node *lln3 = new llist_node((void *)"Vier");
    
    ll->add(0, lln0);
    ll->add(lln0, lln1);
    ll->add(lln1, lln2);
    ll->add(lln2, lln3);
    ll->remove(lln1);
    
    llist_node *node = ll->root();
    
    while(node != 0){
	printf("value == %s\n", (char *)node->value());
	node = node->child();
    }
}
