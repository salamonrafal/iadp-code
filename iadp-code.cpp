/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 * @version 0.0.1
 */
#include <Arduino.h>
#include "common_consts.h"
#include "settings.h"
#include "translations.h"
#include "oled_display.h"
#include "sensors.h"
#include "rtc_time.h"

using namespace Saltronix::OLED_Display;
using namespace Saltronix::Sensor_DHT11;
using namespace Saltronix::Settings;
using namespace Saltronix::Rtc;
using namespace Saltronix::Consts;

struct _S_Def_Settings Settings;
Adafruit_SSD1306 oled_screen_128_64;

DHTesp dht;
TaskHandle_t tempTaskHandle = NULL;

void setup() {
  Serial.begin(SERIAL_SPEED);
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
  displayLeftColumne(oled_screen_128_64, 0, 0);
  displayRightColumne(oled_screen_128_64, 0, false);
  displayNotConnectedSignalWifi(oled_screen_128_64);
  displayAllOnScreen(oled_screen_128_64);
  
  delay(1000);

  Serial.println("--->");
  Serial.print("Settings.sensors.dht_sensor_pin: ");
  Serial.println(Settings.sensors.dht_sensor_pin);
  Serial.println("");
  Serial.print(__DATE__);
  Serial.println(__TIME__);
}

void loop(void) {
  DHTSensorValue DHTSensorData = getDataFromDHTSensor(dht);
  char date[11] = "01.01.2020";
  char chTime[6] = "12:30";
  double dTempAqua = 24;
  //char chTimes[5][6] = {"12:31", "12:32", "12:33", "12:34", "12:35"};

  displayConnectedSignalWifi(oled_screen_128_64);

  displayLeftColumne(oled_screen_128_64, DHTSensorData.temperature, DHTSensorData.humidity);
  displayRightColumne(oled_screen_128_64, dTempAqua, false);
  
  printDate(oled_screen_128_64, date);
  printTime(oled_screen_128_64, chTime);
  Serial.println(DHTSensorData.temperature);
  Serial.println(DHTSensorData.humidity);
  delay(1000);
  /*for(int i = 0; i < 5; i++) {
    printTime(oled_screen_128_64, chTimes[i]);
    displayRightColumne(oled_screen_128_64, 25+i, (25+i % 2 == 0) ? false : true);
    delay(1000);
  }*/
  
}
