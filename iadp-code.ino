#include "settings.h"
#include "translations.h"
#include "oled_display.h"

struct _Def_Settings Settings;
Adafruit_SSD1306 oled_screen_128_64;

void setup() {
  Serial.begin(9600);
  Settings = createMainSettings();

  oled_screen_128_64 = setupDisplayOLED(
    Settings.display_oled.width,
    Settings.display_oled.height,
    Settings.display_oled.mosi_pin,
    Settings.display_oled.sclk_pin,
    Settings.display_oled.dc_pin,
    Settings.display_oled.cs_pin
  );

  drawGrid(oled_screen_128_64);

  //Serial.println(Settings.display_oled.mosi_pin);
  //Serial.println(Settings.display_oled.sclk_pin);
  //Serial.println(Settings.display_oled.dc_pin);
  //Serial.println(Settings.display_oled.rst_pin);
  //Serial.println(Settings.display_oled.cs_pin);
  //Serial.println(Settings.display_oled.width);
  //Serial.println(Settings.display_oled.height);
}

void loop(void) {
  char date[11] = "01.01.2020";
  printDate(oled_screen_128_64, date);
}
