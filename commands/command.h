/*
 * The command classes are for changing settings of skaar. In the very near
 * future there will be two kinds of commands: temporary commands and
 * permanent commands. The temporary commands change the settings only
 * in the current running instance of skaar, and will be lost if skaar
 * shuts down. 
 * However, if you use permanent commands, the changed settings will
 * be saved and restored if you start skaar again.
 * The way to keep the two of them apart from skaars interface is by
 * the first parameter of your command, say for instance the command
 * '/irccolors', or its shorter version '/ic', without the quotes
 * ofcourse. 
 * The use for the permanent version of this command would then be
 * /irccolors -p off
 * or /irccolors -t off for the temporary version.
 * There, you know it. Have fun with it.
*/

#ifndef COMMAND_H
#define COMMAND_H

class command {
    char* c_cmd;
    char* params;
    
public:
    command(char* line, char* par);
    ~command();
    virtual char* get_cmd();
    virtual char* get_params();
    virtual int execute();
    
    /*
     * Checks whether the given char* is a command
     * or not.
    */
    static int is_command(char* line);
    
    /*
     * Converts the given line to a command
    */
    static command* to_command(char* line);
};

#endif
