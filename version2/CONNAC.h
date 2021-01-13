#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SDMBN_H_
#define _SDMBN_H_

#include <stdint.h>
#include <sys/time.h>
#include <pcap/pcap.h>

typedef struct {
	uint32_t nw_src;
	uint32_t nw_src_mask;
	uint32_t nw_dst;
	uint32_t nw_dst_mask;
	uint16_t tp_src;
	uint16_t tp_dst;
    uint16_t dl_type;
	uint8_t nw_proto;
    uint8_t wildcards;
	uint8_t tp_flip;
} PerflowKey;

#define WILDCARD_DL_TYPE    0x01
#define WILDCARD_NW_SRC     0x02
#define WILDCARD_NW_DST     0x04
#define WILDCARD_NW_PROTO   0x08
#define WILDCARD_TP_SRC     0x10
#define WILDCARD_TP_DST     0x20
#define WILDCARD_NW_SRC_MASK    0x40
#define WILDCARD_NW_DST_MASK    0x80
#define WILDCARD_NONE       0x00
#define WILDCARD_ALL        0xFF

//NF should provide
typedef struct {
    //int (*init)();
    //int (*cleanup)();
    int (*get_perflow)();
    int (*put_perflow)(); 
    
} CONNACLocals;

///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
//shared library export
int connac_init(CONNACLocals *locals);
int connac_cleanup();
//int connac_send_perflow();

#endif

#ifdef __cplusplus
}
#endif
