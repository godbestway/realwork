CFLAGS += -Wall -g 
LDFLAGS +=  -lpthread -lpcap -lprotobuf-c -Wl,--no-undefined 

all: connac

connac: main.o conn.o config.o connac_state.o information.pb-c.o
	gcc main.o config.o conn.o connac_state.o information.pb-c.o -o connac $(CFLAGS) $(LDFLAGS)

information.pb-c.o: information.pb-c.c 
	gcc -c $(CFLAGS) $(LDFLAGS) information.pb-c.h information.pb-c.c

conn.o: conn.c 
	gcc -c $(CFLAGS) $(LDFLAGS) conn.c conn.h

config.o: config.c 
	gcc -c $(CFLAGS) $(LDFLAGS) config.c config.h

connac_state.o: connac_state.c 
	gcc -c $(CFLAGS) $(LDFLAGS) connac_state.c connac_state.h

main.o: main.c 
	gcc -c $(CFLAGS) $(LDFLAGS) main.c

clean: 
	rm -rf main.o conn.o config.o connac_state.o
