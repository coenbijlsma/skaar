#include <stdio.h>
#include <string.h>

#include "command.h"

int main(int argc, char** argv){
    command* blaat = command::to_command("/commando 1 2 3 4");
}
