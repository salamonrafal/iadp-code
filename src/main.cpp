#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "modules/oled/views.h"
#include "modules/dht11/dht11.h"
#include "modules/rtc/rtc_module.h"
#include "modules/hbridge/hbridge.h"
#include "modules/wifi/wifi.h"

void getRoomTemperaure();

void setup() {
  Serial.begin(38400);
  
  // Setup Modules
  setupDisplayOLED();
  setupDHT11();
  setupRTCModule();
  
  // Welcome screen
  displaySplashScreen();
  displayAllOnScreen();
  setupBridge();
  setUpWiFiServer();
}

void loop() {
  double dAquariumTemperatureValue = 24;
  bool bIsWatherLevelToLowValue = true;
  bool bIsWifiConnectedValue = WiFi.status() == WL_CONNECTED ? true : false;
  
  getRoomTemperaure();
  getDateTimeFromRTCModule();

  handleRestCalls();
  
  showMainView(
    chRtcDateValue, 
    chRtcTimeValue, 
    dAquariumTemperatureValue, 
    bIsWatherLevelToLowValue, 
    stSensorDHTValue, 
    bIsWifiConnectedValue
  );
}

void getRoomTemperaure() {
  if (!tasksEnabled) {
    // Wait 2 seconds to let system settle down
    delay(2000);
    // Enable task that will read values from the DHT sensor
    tasksEnabled = true;
    if (tempTaskHandle != NULL) {
			vTaskResume(tempTaskHandle);
		}
  }
  yield();
}