#ifndef _CONFIGS_H_
#define _CONFIGS_H_

#include "app_config.h"

#if !APP_CONFIG_SETUP_WIFI
    char ssid[64] = "";
    char password[64] = "";
#endif

bool config_check_setup_wifi(void)
{
    return APP_CONFIG_SETUP_WIFI;
}

#endif