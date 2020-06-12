#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "modules/oled/views.h"
#include "modules/dht11/dht11.h"
#include "modules/rtc/rtc_module.h"
#include "modules/hbridge/hbridge.h"
#include "modules/wifi/wifi.h"
#include "helpers/configs.h"

void getRoomTemperaure();
bool bIsWifiConnectedValue = false;

void setup() {
  Serial.begin(9600);

  // Setup Modules
  setupDisplayOLED();
  setupDHT11();
  setupRTCModule();
  
  // Welcome screen
  displaySplashScreen();
  displayAllOnScreen();
  setupBridge();

  if (config_check_setup_wifi()) {
    setUpWiFiServer(ssid, password);
    bIsWifiConnectedValue = WiFi.status() == WL_CONNECTED ? true : false;
  }
}

void loop() {
  double dAquariumTemperatureValue = 24;
  bool bIsWatherLevelToLowValue = true;
  
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