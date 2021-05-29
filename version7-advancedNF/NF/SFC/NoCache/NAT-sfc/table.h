/*
   Copyright (C) 2010  Infertux <infertux@infertux.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <time.h>
#include <linux/types.h>
#include <pcap.h>
#include <libnet.h>
#include <pthread.h>
#include <netinet/ip.h>
#include <CONNAC.h>

#ifndef ETH_ALEN
#define ETH_ALEN 6
#endif

#define MIN_EXTERNAL_PORT 1024
#define MAX_EXTERNAL_PORT 65535
#define RECORD_TIMEOUT 60000 /* in seconds */
#define BUCKET_SIZE  31337

#define CXT_HASH4(src,dst,sp,dp,pr) \
   (( src + dst + sp + dp + pr) % BUCKET_SIZE)

/* Verbosity level */
enum print_mode {PRINT_ALL, PRINT_BRIEF};

/* A node in our linked-list table */
typedef struct _connState {
    uint8_t     internal_mac[ETH_ALEN];
    uint32_t    internal_ip;
    uint16_t    internal_port;
    uint32_t    external_ip;
    uint8_t	proto;
    uint32_t    hash;
    uint32_t 	nat_hash;
    uint32_t    cxid;
    struct _connState *prev;
    struct _connState *next;
}connState;

typedef struct _actionState {
    uint32_t    external_ip;
    uint16_t    external_port;
    uint32_t    hash;
    uint32_t    nat_hash;
    uint32_t    cxid;
    time_t      touch;
    struct _actionState *prev;
    struct _actionState *next;
}actionState;

typedef struct _packetinfo {
	struct ethhdr *eth;
	struct iphdr *ip; 
	u_int16_t src_port;
	u_int16_t dst_port;
	uint32_t hash;
	uint32_t nat_hash;
	uint32_t cxid;
}packetinfo;

typedef struct
{
    int cxid;
    int hash;
}Match;

/* Our functions prototypes */
void table_print(enum print_mode mode);

connState* conn_table_outbound(packetinfo* pi);
actionState *action_table_outbound(packetinfo* pi);
int conn_table_inbound(packetinfo* pi);
connState *action_table_inbound(packetinfo* pi);

uint16_t table_get_external_port(uint32_t hash,uint32_t cxid);

void state_expunge_expired();

int local_conn_get_one_perflow(connState * conn_state);
int local_conn_get_perflow();
int local_conn_put_perflow(ConnState* recv_state);

int local_action_get_one_perflow(Match *match);
int local_action_get_perflow();
int local_action_put_perflow(ActionState* recv_state);

void showConnState(connState* conn_state);
void showActionState(actionState* action_state);
void showAllState();





