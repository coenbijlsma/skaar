
all: client

client: stringtokenizer.o client_conn.o message.o pass_message.o nick_message.o user_message.o oper_message.o quit_message.o join_message.o mode_message.o privmsg_message.o client.o ui.o main.o
	g++ -lncurses stringtokenizer.o client_conn.o message.o pass_message.o nick_message.o user_message.o oper_message.o quit_message.o join_message.o mode_message.o privmsg_message.o client.o main.o -o client

stringtokenizer.o: tools/stringtokenizer.h tools/stringtokenizer.cpp    
	g++ -c tools/stringtokenizer.cpp

client_conn.o: client_conn.h client_conn.cpp
	g++ -c client_conn.cpp

message.o: messages/message.h messages/message.cpp
	g++ -c messages/message.cpp

pass_message.o: messages/out/pass_message.h messages/out/pass_message.cpp
	g++ -c messages/out/pass_message.cpp

nick_message.o: messages/out/nick_message.h messages/out/nick_message.cpp
	g++ -c messages/out/nick_message.cpp

user_message.o: messages/out/user_message.h messages/out/user_message.cpp
	g++ -c messages/out/user_message.cpp

oper_message.o: messages/out/oper_message.h messages/out/oper_message.cpp
	g++ -c messages/out/oper_message.cpp

quit_message.o: messages/out/quit_message.h messages/out/quit_message.cpp
	g++ -c messages/out/quit_message.cpp

join_message.o: messages/out/join_message.h messages/out/join_message.cpp
	g++ -c messages/out/join_message.cpp

mode_message.o: messages/out/mode_message.h messages/out/mode_message.cpp
	g++ -c messages/out/mode_message.cpp

privmsg_message.o: messages/out/privmsg_message.h messages/out/privmsg_message.cpp
	g++ -c messages/out/privmsg_message.cpp

client.o: client.h client.cpp
	g++ -c client.cpp

ui.o: virtualui.h exampleui.cpp
	g++ -c exampleui.cpp

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm *.o
	rm client

.PHONY: all clean
