#ifndef _WIFI_H_
#define _WIFI_H_

#include <WiFi.h>
#include <aREST.h>

#define DEVICE_ID "9b51f25e"
#define WIFI_CONNECT_DELAY_TRY 1000

aREST rest = aREST();

const char *pingVariable = "pong";
const char *device_name = "iadp-1.0.0-esp32-30";
int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setUpWiFiServer(char ssid[64], char pwd[64])
{
  rest.variable("ping", &pingVariable);

  rest.set_id(DEVICE_ID);
  rest.set_name(device_name);

  while ( status != WL_CONNECTED) {
    WiFi.setHostname(device_name);
    status = WiFi.begin(ssid, pwd);
    delay(WIFI_CONNECT_DELAY_TRY);
  }
  
  Serial.println(WiFi.localIP());
  server.begin();
}

void handleRestCalls(void)
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