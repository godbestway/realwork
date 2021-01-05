#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ConnacConfig_H_
#define _ConnacConfig_H_

#include <stdint.h>
#include <sys/time.h>
#include <pcap.h>

///// DEFINES ////////////////////////////////////////////////////////////////
#define CONFIG_FILE "config.conf"
#define CONF_KEY_LEN    32
#define CONF_VALUE_LEN  32

#define CONF_CTRL_IP_DEFAULT            "192.168.5.1"
#define CONF_CTRL_PORT_STATE_DEFAULT    18080


#define CONF_CTRL_IP_LEN  16

#define CONF_CTRL_IP            "ctrl_ip"
#define CONF_CTRL_PORT_STATE    "ctrl_port_state"

///// STRUCTURES /////////////////////////////////////////////////////////////
typedef struct {
    char ctrl_ip[CONF_CTRL_IP_LEN];
	uint16_t ctrl_port_state;
} ConnacConfig;

///// FUNCTION PROTOTYPES ////////////////////////////////////////////////////
int connac_parse_config();

#endif

#ifdef __cplusplus
}
#endif
