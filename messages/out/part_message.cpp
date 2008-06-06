#incude "part_message.h"

part_message::part_message(char* msg, client* cl, char* chans) : message(msg, cl) {
}

part_message::~part_message(){}

char* part_message::get_chans(){
}

char* part_message::to_string(int rfc){
}
