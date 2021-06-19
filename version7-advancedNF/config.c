#include "debug.h"
#include "config.h"
#include "connac_core.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef CONFIG_DIR
#define CONFIG_DIR "./"
#endif

int connac_parse_config()
{
    // Set defaults
    snprintf(connac_config.ctrl_ip, CONF_CTRL_IP_LEN, CONF_CTRL_IP_DEFAULT);
    connac_config.ctrl_port_conn = CONF_CTRL_PORT_CONN_DEFAULT;
    connac_config.ctrl_port_action = CONF_CTRL_PORT_ACTION_DEFAULT;
    connac_config.ctrl_share =  CONF_CTRL_SHARE_DEFAULT;
    connac_config.ctrl_sfc = CONF_CTRL_SFC_DEFAULT;
    connac_config.ctrl_adnatfire = CONF_CTRL_ADNATFIRE_DEFAULT;
    
#define FILEPATH_LEN 256
    char filepath[FILEPATH_LEN];
    snprintf(filepath, FILEPATH_LEN, "%s/%s", CONFIG_DIR, CONFIG_FILE);

    FILE *file = fopen(filepath, "r");
    if (NULL == file)
    { 
        ERROR_PRINT("Failed to open config file '%s': %s", filepath, 
                strerror(errno));
        return -1; 
    }

    char key[CONF_KEY_LEN];
    char value[CONF_VALUE_LEN];
    while (2 == fscanf(file, "%s = %s\n", key, value))
    {
        if (0 == strncmp(key, CONF_CTRL_IP, 7))
        { strncpy(connac_config.ctrl_ip, value, CONF_CTRL_IP_LEN); } 
        else if (0 == strncmp(key, CONF_CTRL_PORT_CONN, 15))
        { connac_config.ctrl_port_conn = atoi(value); }
	else if (0 == strncmp(key, CONF_CTRL_PORT_ACTION, 15))
        { connac_config.ctrl_port_action = atoi(value); }
	else if (0 == strncmp(key, CONF_CTRL_SHARE, 10))
        { connac_config.ctrl_share = atoi(value); }
	else if (0 == strncmp(key, CONF_CTRL_SFC, 8))
        { connac_config.ctrl_sfc = atoi(value); }
	else if (0 == strncmp(key, CONF_CTRL_ADNATFIRE, 14))
        { connac_config.ctrl_adnatfire = atoi(value); }
	else if (0 == strncmp(key, CONF_CTRL_COPY, 10))
        { connac_config.ctrl_copy = atoi(value); }
    }

    if (fclose(file) != 0)
    {
        ERROR_PRINT("Failed to close config file '%s': %s", filepath, 
                strerror(errno));
        return -1; 
    }

    return 0;
}
