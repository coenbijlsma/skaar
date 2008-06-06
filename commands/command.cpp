#include "command.h"

#include "../tools/stringtokenizer.h"

command::command(char* cmd, char* par){
    if(cmd == 0 || strlen(cmd) == 0){
	fprintf(stderr, "The command cannot be NULL\n");
    }
    c_cmd = cmd;
    params = par;
    
    stringtokenizer* st = new stringtokenizer(params, ' ');
    while(st->has_next()){
	printf("\"%s\"\n", st->next());
    }
}

command::~command(){}

char* command::get_cmd(){
    char* t_cmd = (char*)malloc(strlen(c_cmd) +1);
    memset(t_cmd, 0, strlen(c_cmd) +1);
    strcpy(t_cmd, c_cmd);
    return t_cmd;
}

char* command::get_params(){
    if(params == 0 || strlen(params) == 0){
	return 0;
    }
    
    char* t_params = (char*)malloc(strlen(params) +1);
    memset(t_params, 0, strlen(params) +1);
    strcpy(t_params, params);
    return t_params;
}

int command::execute(){
    return -1;
}

int command::is_command(char* line){
    fprintf(stderr, "Not yet implemented: command::is_command(char* line)\n");
    return -1;
}

command* command::to_command(char* line){
    char* cmd;
    char* params;
    char* s_pos = strchr(line, ' ');
    if(s_pos == 0){
	return 0;
    }
    
    cmd = (char*)malloc(s_pos - line);
    memset(cmd, 0, s_pos - line);
    strncpy(cmd, line, s_pos - line);
    //printf("cmd == \"%s\"\n", cmd);
    
    params = (char*)malloc(strlen(s_pos));
    memset(params, 0, strlen(s_pos));
    strcpy(params, (s_pos +1));
    //printf("params == \"%s\"\n", params);

    return new command(cmd, params);
}
