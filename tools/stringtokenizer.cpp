#include "stringtokenizer.h"

stringtokenizer::stringtokenizer(char* seq, char delim){
    char* ptr;
    if(seq == 0){
	fprintf(stderr, "The seqnence to be checked cannot be NULL\n");
	return;
    }else{
	sequence = seq;
    }
    
    if(delim == 0){
	delimeter = ' ';
    }else{
	delimeter = delim;
    }

    cloc = 0;
    ctok = 0;
    if( (ptr = strchr(seq, delim)) == 0){
	ntok = (char*)malloc(strlen(seq) +1);
	memset(ntok, 0, strlen(seq) +1);
	strcpy(ntok, seq);
    }else{
	ntok = (char*)malloc(ptr - seq + 1);
	memset(ntok, 0, ptr - seq + 1);
	strncpy(ntok, seq, ptr - seq);
	cloc = ptr - seq;
    }
    
}

stringtokenizer::~stringtokenizer(){
    free(ctok);
    free(ntok);
}

int stringtokenizer::has_next(){
    if(ntok == 0){
	return 0;
    }
    return 1;
}

int stringtokenizer::cnttok(){
    int i;
    int tok = 1;
    
    for(int i = 0; i <= strlen(sequence); i++){
	if(sequence[i] == delimeter){
	    tok++;
	}
    }
    return tok;
}

char* stringtokenizer::next(){
    char* ptr;
    char* ptr2;
    char* retval;
    int i;
    
    if(ntok == 0){
	return 0;
    }
    
    if(ctok != 0){
	free(ctok);
    }
    
    // copy ntok into ctok
    ctok = (char*)malloc(strlen(ntok) +1);
    memset(ctok, 0, strlen(ntok) +1);
    strcpy(ctok, ntok);
    
    // shift until next delimeter
    for(ptr = sequence + cloc; ptr[0] != '\0' && ptr[0] != delimeter; ptr++){}
    
    //(re)fill ntok
    free(ntok);
    if(ptr[0] == '\0'){
	ntok = 0;
    }else{
	ptr++;
	ptr2 = strchr(ptr, delimeter);
	
	if(ptr2 == 0){
	    // if this is the last token
	    ntok = (char*)malloc(strlen(ptr) +1);
	    memset(ntok, 0, strlen(ptr) +1);
	    strcpy(ntok, ptr);
	}else{
	    ntok = (char*)malloc(ptr2 - ptr + 1);
	    memset(ntok, 0, ptr2 - ptr + 1);
	    strncpy(ntok, ptr, ptr2 - ptr);
	}
	cloc += strlen(ntok) + 1;
    }
    
    retval = (char*)malloc(strlen(ctok) +1);
    memset(retval, 0, strlen(ctok) +1);
    strcpy(retval, ctok);
    return retval;
}
