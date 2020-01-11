#include <Arduino.h>
#include "settings.h"
#include "translations.h"
#include "oled_display.h"
#include "sensors.h"

using namespace Saltronix::OLED_Display;
using namespace Saltronix::Sensor_DHT11;
using namespace Saltronix::Settings;

struct _Def_Settings Settings;
Adafruit_SSD1306 oled_screen_128_64;

DHTesp dht;
TaskHandle_t tempTaskHandle = NULL;

void setup() {
  Serial.begin(38400);
  Settings = createMainSettings();

  dht = setupDHTSensor(Settings.sensors.dht_sensor_pin);
  
  oled_screen_128_64 = setupDisplayOLED(
    Settings.display_oled.width,
    Settings.display_oled.height,
    Settings.display_oled.mosi_pin,
    Settings.display_oled.sclk_pin,
    Settings.display_oled.dc_pin,
    Settings.display_oled.cs_pin
  );

  displaySplashScreen(oled_screen_128_64);
  delay(5000);
  drawGrid(oled_screen_128_64);
  
  Serial.println("--->");
  Serial.print("Settings.sensors.dht_sensor_pin: ");
  Serial.println(Settings.sensors.dht_sensor_pin);
}

void loop(void) {
  DHTSensorValue DHTSensorData = getDataFromDHTSensor(dht);
  char date[11] = "01.01.2020";
  char chTime[6] = "12:30";
  double dTempAqua = 24;
  char chTimes[5][6] = {"12:31", "12:32", "12:33", "12:34", "12:35"};

  displayConnectedSignalWifi(oled_screen_128_64);

  displayLeftColumne(oled_screen_128_64, DHTSensorData.temperature, DHTSensorData.humidity);
  displayRightColumne(oled_screen_128_64, dTempAqua, false);
  
  printDate(oled_screen_128_64, date);
  printTime(oled_screen_128_64, chTime);
  delay(1000);
  
  displayNotConnectedSignalWifi(oled_screen_128_64);
  
  for(int i = 0; i < 5; i++) {
    printTime(oled_screen_128_64, chTimes[i]);
    displayRightColumne(oled_screen_128_64, 25+i, (25+i % 2 == 0) ? false : true);
    delay(1000);
  }
  
}
