#ifndef _OLED_DISPLAY_
#define _OLED_DISPLAY_

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



Adafruit_SSD1306 _oled_screen_128_64;

/**
 * 
 */
Adafruit_SSD1306 setupDisplayOLED(
  int width, 
  int height, 
  int mosi_pin, 
  int sclk_pin, 
  int dc_pin, 
  unsigned int rst_pin, 
  int cs_pin
) {
  Adafruit_SSD1306 _oled_screen_128_64 (
    width, 
    height, 
    mosi_pin, 
    sclk_pin, 
    dc_pin, 
    rst_pin, 
    cs_pin
  );

  _oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
  _oled_screen_128_64.clearDisplay();
  
  _oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
  _oled_screen_128_64.clearDisplay();
  
  _oled_screen_128_64.clearDisplay();
  _oled_screen_128_64.setTextSize(1);
  _oled_screen_128_64.setTextColor(WHITE);

  return _oled_screen_128_64;
}


void drawGrid(Adafruit_SSD1306 &oled_screen_128_64) {
  oled_screen_128_64.drawFastHLine(0, 16, 128, WHITE);
  oled_screen_128_64.drawFastVLine(64, 16, 48, WHITE);
  oled_screen_128_64.display();
}

void printDate(Adafruit_SSD1306 &oled_screen_128_64, uint8_t date) {
  oled_screen_128_64.fillRect(0, 0, 12, 10, BLACK);
  oled_screen_128_64.setCursor(1, 1);
  oled_screen_128_64.print(date);
  oled_screen_128_64.display();
}

#endif //_OLED_DISPLAY_
