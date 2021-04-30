CFLAGS += -Wall -g 
LDFLAGS +=  -lpthread -lpcap -lprotobuf-c -Wl,--no-undefined 

all: connac

connac: main.o conn.o config.o connac_state.o connac_ac.o information.pb-c.o person.pb-c.o syn.pb-c.o protoObject.o
	gcc main.o config.o conn.o connac_state.o connac_ac.o information.pb-c.o person.pb-c.o syn.pb-c.o protoObject.o -o connac $(CFLAGS) $(LDFLAGS)

person.pb-c.o: person.pb-c.c 
	gcc -c $(CFLAGS) $(LDFLAGS) person.pb-c.h person.pb-c.c

information.pb-c.o: information.pb-c.c 
	gcc -c $(CFLAGS) $(LDFLAGS) information.pb-c.h information.pb-c.c

syn.pb-c.o: syn.pb-c.c 
	gcc -c $(CFLAGS) $(LDFLAGS) syn.pb-c.h syn.pb-c.c

conn.o: conn.c 
	gcc -c $(CFLAGS) $(LDFLAGS) conn.c conn.h

protoObject.o: protoObject.c 
	gcc -c $(CFLAGS) $(LDFLAGS) protoObject.c protoObject.h


config.o: config.c 
	gcc -c $(CFLAGS) $(LDFLAGS) config.c config.h

connac_state.o: connac_state.c 
	gcc -c $(CFLAGS) $(LDFLAGS) connac_state.c connac_state.h

connac_ac.o: connac_ac.c 
	gcc -c $(CFLAGS) $(LDFLAGS) connac_ac.c connac_ac.h


main.o: main.c 
	gcc -c $(CFLAGS) $(LDFLAGS) main.c

clean: 
	rm -rf main.o conn.o config.o protoObject.o connac_state.o
