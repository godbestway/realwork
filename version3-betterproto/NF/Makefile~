CFLAGS += -Wall -g 
LDFLAGS +=  -lpthread -lpcap -lconnac -lprotobuf-c -Wl,--no-undefined 

SOURCES = main.c 
CC = gcc

all : realnf

realnf : ${SOURCES:.c=.o}
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) -c $^


clean: 
	rm -rf main.o
