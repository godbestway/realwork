GXX=/usr/bin/clang
GCC=/usr/bin/gcc
FLAGS=-lpcap -lpcre -lresolv -lsdmbn -ljson-c -lpthread -std=gnu99 -ggdb 
FILES=read.c packets.c rules.c handle_packets.c state.c serialize.c
OUTPUT=firewall

make :
	${GCC} ${FILES} ${FLAGS} -o ${OUTPUT}
