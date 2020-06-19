/**
 * @file wifi.h
 * @author Rafał Salamon (rasa@salamonrafal.pl)
 * @brief 
 * @version 0.1
 * @date 2020-06-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef _WIFI_H_
#define _WIFI_H_

#include <WiFi.h>
#include <aREST.h>
#include "wifi_setup_st.h"

#define DEVICE_ID "9b51f25e"
#define WIFI_CONNECT_DELAY_TRY 10000
#define WIFI_MAX_RECONNECTIONS 6

aREST rest = aREST();

const char *pingVariable = "pong";
const char *device_name = "iadp-1.0.0-esp32-30";
int status = WL_IDLE_STATUS;
IPAddress localIp;

WiFiServer server(80);

/**
 * @brief Setup WiFi Server object
 * 
 * @param ssid 
 * @param pwd 
 */
void set_up_wifi_server(const char ssid[64], const char pwd[128])
{
  volatile unsigned int inx = 0;

  while ( status != WL_CONNECTED) {
    WiFi.setHostname(device_name);
    status = WiFi.begin(ssid, pwd);

    Serial.println(inx);
    Serial.println(status);
    Serial.println(ssid);
    Serial.println(pwd);
    Serial.println("-----");

    if (inx++ == WIFI_MAX_RECONNECTIONS) {
      return;
    }

    delay(WIFI_CONNECT_DELAY_TRY);
  }

  localIp = WiFi.localIP();
  Serial.println(localIp.toString());
  server.begin();
}

/**
 * @brief Setup api endpoints object
 * 
 * @param Endpoints 
 */
void setup_api_endpoints(Wifi_Setup_T Endpoints) 
{
  rest.variable("ping", Endpoints.ping);
  rest.set_id(DEVICE_ID);
  rest.set_name(device_name);
}

/**
 * @brief Handle rest calls
 */
void handle_rest_calls(void)
{
    WiFiClient client = server.available();
    
    if (!client) {
        return;
    }

    while(!client.available()){
        delay(1);
    }

    rest.handle(client);
}
#endif