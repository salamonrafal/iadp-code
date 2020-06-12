#ifndef _WIFI_H_
#define _WIFI_H_

#include <WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "SalamonNet24";
const char* password = "Grzegorz84$";
const char* deviceId = "9b51f25e";
const char* deviceName = "iadp-1.0.0-esp32-30";
const char* pingVariable = "pong";
int status = WL_IDLE_STATUS;
const unsigned int wifiConnectDelayTry = 1000;

// Create an instance of the server
WiFiServer server(80);

void setUpWiFiServer(void)
{
  rest.variable("ping", &pingVariable);

  rest.set_id(deviceId);
  rest.set_name(deviceName);

  while ( status != WL_CONNECTED) {
    WiFi.setHostname(deviceName);
    status = WiFi.begin(ssid, password);
    delay(wifiConnectDelayTry);
  }
  
  Serial.println(WiFi.localIP());
  server.begin();
}

void handleRestCalls(void)
{
    // Handle REST calls
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