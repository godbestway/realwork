#include "main.h"
#include "debug.h"
#include "config.h"
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
    connac_config.ctrl_port_state = CONF_CTRL_PORT_STATE_DEFAULT;
    
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
        else if (0 == strncmp(key, CONF_CTRL_PORT_STATE, 15))
        { connac_config.ctrl_port_state = atoi(value); }
    }

    if (fclose(file) != 0)
    {
        ERROR_PRINT("Failed to close config file '%s': %s", filepath, 
                strerror(errno));
        return -1; 
    }

    return 0;
}
