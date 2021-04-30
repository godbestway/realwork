CFLAGS += -Wall -g 
LDFLAGS +=  -lpthread -lpcap -lprotobuf-c -Wl,--no-undefined 

SOURCES = main.c conn.c config.c connac_state.c connac_ac.c information.pb-c.c person.pb-c.c syn.pb-c.c protoObject.c
CC = gcc

#person.pb-c.o: person.pb-c.c 
#	gcc -c $(CFLAGS) $(LDFLAGS) person.pb-c.h person.pb-c.c

all : connac

connac : ${SOURCES:.c=.o}
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) -c $^



#main.o: main.c 
#	gcc -c $(CFLAGS) $(LDFLAGS) main.c

clean: 
	rm -rf main.o conn.o config.o protoObject.o connac_state.o connac_ac.o
