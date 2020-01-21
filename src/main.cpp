#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "modules/oled/views.h"
#include "modules/dht11/dht11.h"
#include "modules/rtc/rtc_module.h"
#include "modules/hbridge/hbridge.h"

void getRoomTemperaure();

void setup() {
  Serial.begin(38400);
  
  // Setup Modules
  setupDisplayOLED();
  setupDHT11();
  setupRTCModule();
  setupBridge();

  // Welcome screen
  displaySplashScreen();
  displayAllOnScreen();
  delay(5000);
}

void loop() {
  double dAquariumTemperatureValue = 24;
  bool bIsWatherLevelToLowValue = true;
  bool bIsWifiConnectedValue = false;
  
  getRoomTemperaure();
  getDateTimeFromRTCModule();
  
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