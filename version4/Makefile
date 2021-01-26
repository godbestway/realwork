SOURCES= connac_core.c conn.c config.c connac_state.c connac_ac.c information.pb-c.c person.pb-c.c syn.pb-c.c connGetPerflowMsg.pb-c.c actionGetPerflowMsg.pb-c.c connPutPerflowMsg.pb-c.c actionPutPerflowMsg.pb-c.c connPutPerflowAckMsg.pb-c.c actionPutPerflowAckMsg.pb-c.c ConnState.pb-c.c ActionState.pb-c.c connGetPerflowAckMsg.pb-c.c actionGetPerflowAckMsg.pb-c.c protoObject.c
CC = gcc

ifeq (${PREFIX},)
PREFIX=/usr/local/
endif
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include
CONFDIR=${PREFIX}/etc

CFLAGS += -Wall -g -DCONFIG_DIR='"${CONFDIR}/"'
LDFLAGS += -lpthread -lpcap -lprotobuf-c -Wl,--no-undefined

build: libconnac.so

libconnac.so: ${SOURCES:.c=.o}
	$(CC) -o $@ -shared $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -fpic -c $^

install: build 
	install -d ${LIBDIR}
	install libconnac.so ${LIBDIR}/libconnac.so
	install -d ${INCLUDEDIR}
	install CONNAC.h ${INCLUDEDIR}/CONNAC.h
	install ConnState.pb-c.h ${INCLUDEDIR}/ConnState.pb-c.h
	install ActionState.pb-c.h ${INCLUDEDIR}/ActionState.pb-c.h
	install -d ${CONFDIR}
	if [ ! -f ${CONFDIR}/config.conf ]; then install config.conf ${CONFDIR}/config.conf; fi

clean:
	rm *.o *.so *.gch

