#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arraylist.h"

arraylist::arraylist(){
    _size = 0;
    //_array = new void*[_size +1];
    //printf("[DEBUG] INIT\n");
}

arraylist::arraylist(void** data){
    _size = (sizeof(data) / sizeof(int)) -1;
    _array = new void*[_size +1];
    
    for(int i = 0; i < (_size); i++){
	void* _pv = malloc(sizeof(void*));
	memset(_pv, 0, sizeof(_pv));
	_array[i] = memcpy(_pv, data[i], sizeof(data[i]));
    }
}

arraylist::~arraylist(){}

int arraylist::add(void *elem){	
    // Create a new array that contains one extra element
    void** tmp_array = new void*[_size++];
    
    if(_size > 1){
	if(deep_copy(_array, tmp_array) != 0){
	    fprintf(stderr, "Error while copying arrays!\n");
	    return 1;
	}
    }
    
    //printf("%d\n", _size);
    tmp_array[_size -1] = elem;
    _array = tmp_array;
    return 0;
}

int arraylist::add(int pos, void *elem){
    if(pos > (_size -1) ){
	fprintf(stderr, "Position not in array(%d)\n", pos);
	return 1;
    }
    
    void** tmp_array = new void*[_size++];
    
    if(_size > 1){
	if(deep_copy_except(_array, tmp_array, pos) != 0){
	    fprintf(stderr, "Error while copying arrays!\n");
	    return 1;
	}
    }
    
    tmp_array[pos] = elem;
    _array = tmp_array;
    return 0;
}

void arraylist::clear(){
    _array = (void**)0;
}

arraylist* arraylist::clone(){
    return new arraylist(_array);
}

int arraylist::contains(void *elem){
    return 0;
}

void *arraylist::get(int pos){
    if(pos > (_size -1)){
	fprintf(stderr, "position not in array!\n");
	return (void*)0;
    }
    return (void*)_array[pos];
}

int arraylist::remove(int pos){
    return 0;
}

int arraylist::remove(void *elem){
    return 0;
}

int arraylist::size(){
    return _size;
}

void** arraylist::to_array(){
    return _array;
}

// PRIV
int arraylist::deep_copy(void** from, void** to){
    //printf("[DEBUG] deep_copy\n");
    if( (sizeof(to) / sizeof(int)) < (sizeof(from) / sizeof(int))){
	//printf("1\n");
	return 1;
    }else{
	for(int i = 0; i < _size; i++){
	    to[i] = from[i];
	}
    }
    return 0;
}

int arraylist::deep_copy_except(void** from, void** to, int except){
    //printf("[DEBUG] deep_copy_except(%d, %d, %d)\n", from, to, except);
    if( (sizeof(to) / sizeof(int)) <  (sizeof(from) / sizeof(int) )){
	fprintf(stderr, "1\n");
	return 1;
    }else{
	for(int i = 0; i < _size; i++){
	    void* elem = from[i];
	    if(i < except){
		to[i] = elem;
	    }else{
		to[i+1] = elem;
	    }
	}
    }
    return 0;
}
