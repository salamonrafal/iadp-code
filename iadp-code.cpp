/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 * @version 0.0.1
 */
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "Saltronix/Consts/common_consts.h"
#include "Saltronix/Settings/settings.h"
#include "Saltronix/Consts/translations.h"
#include "Saltronix/Display/oled_display.h"
#include "Saltronix/Sensors/dht11.h"
#include "Saltronix/Rtc/ds3231.h"
#include "views/main.h"

using namespace Saltronix::Display::OLED;
using namespace Saltronix::Sensors::DHT11;
using namespace Saltronix::Settings;
using namespace Saltronix::Rtc::DS3231;
using namespace Saltronix::Consts;
using namespace Saltronix::Views;
using namespace Saltronix::Consts::Translations;

struct _S_Def_Settings Settings;
Adafruit_SSD1306 oled_screen_128_64;

DHTesp dht;
TaskHandle_t tempTaskHandle = NULL;


void setup() {
  DHTSensorValue tempDht11Data;
  char cDate[11] = "00.00.0000";
  char cTime[6] = "00:00";

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

  tempDht11Data.humidity = 0;
  tempDht11Data.temperature = 0;

  displaySplashScreen(oled_screen_128_64);
  delay(5000);

  drawGrid(oled_screen_128_64);
  drawMainPage(oled_screen_128_64, cDate, cTime, tempDht11Data, 0.0, false, false);
  displayAllOnScreen(oled_screen_128_64);
  
  delay(100);

  Serial.println("--->");
  Serial.print("Settings.sensors.dht_sensor_pin: ");
  Serial.println(Settings.sensors.dht_sensor_pin);
  Serial.println("");
  Serial.print(__DATE__);
  Serial.println(__TIME__);
}

void loop(void) {
  DHTSensorValue DHTSensorData = getDataFromDHTSensor(dht);
  char cDate[11] = "01.01.2020";
  char cTime[6] = "12:30";
  double dTempAqua = 24;

  drawMainPage(oled_screen_128_64, cDate, cTime, DHTSensorData, dTempAqua, false, false);
  
  Serial.println(DHTSensorData.temperature);
  Serial.println(DHTSensorData.humidity);
  delay(5000);
}
