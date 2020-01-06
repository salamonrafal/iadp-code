/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 */
#ifndef _OLED_DISPLAY_
#define _OLED_DISPLAY_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "icons.h"

/*
 * CONST
 */

#define OLED_FONT_SIZE 7

/*
 * [PUBLIC METHODS]
 */

/**
 * Initial OLED display
 * 
 * @param width number of pixels defined width of screen
 * @param height number of pixels defined height of screen
 * @param mosi_pin number of MOSI PIN on Arduino
 * @param sclk_pin number of SCLK / CLK PIN on Arduino
 * @param dc_pin number of DC PIN on Arduino
 * @param cs_pin number of CS PIN on Arduino
 * 
 * @return class of manage display screen
 */
Adafruit_SSD1306 setupDisplayOLED(
  int width, 
  int height, 
  int mosi_pin, 
  int sclk_pin, 
  int dc_pin, 
  int cs_pin
) {
  Adafruit_SSD1306 _oled_screen_128_64 (
    width, 
    height, 
    mosi_pin, 
    sclk_pin, 
    dc_pin, 
    -1, 
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

/**
 * Drawing on blue screen grid (bottom color screen)
 * 
 * @param oled_screen_128_64 reference to Adafruit class 
 */
void drawGrid(Adafruit_SSD1306 &oled_screen_128_64) {
  oled_screen_128_64.drawFastHLine(0, 16, 128, WHITE);
  oled_screen_128_64.drawFastVLine(64, 16, 48, WHITE);
  oled_screen_128_64.display();
}

/**
 * Drawing on yellow screen current date (top color screen)
 * 
 * @param oled_screen_128_64 reference to Adafruit class
 * @param chDate[11] current date to display max 10 chars
 */
void printDate(Adafruit_SSD1306 &oled_screen_128_64, char chDate[11]) {
  int poxX = 0;
  int posY = 0;
  
  oled_screen_128_64.fillRect(poxX, posY, 60, OLED_FONT_SIZE, BLACK);
  oled_screen_128_64.setCursor(poxX, posY);
  oled_screen_128_64.setTextSize(0.3);
  oled_screen_128_64.setTextColor(WHITE);
  oled_screen_128_64.print(chDate);
  
  oled_screen_128_64.display();
}

/**
 * Drawing on yellow screen current time
 * 
 * @param oled_screen_128_64 reference to Adafruit class
 * @param chTime[6] current time to display max 5 chars
 */
void printTime(Adafruit_SSD1306 &oled_screen_128_64, char chTime[6]) {
  int poxX = 30;
  int posY = 9;
  
  oled_screen_128_64.fillRect(poxX, posY, 29, OLED_FONT_SIZE, BLACK);
  oled_screen_128_64.setCursor(poxX, posY);
  oled_screen_128_64.setTextSize(0.1);
  oled_screen_128_64.setTextColor(WHITE);
  oled_screen_128_64.print(chTime);
  oled_screen_128_64.display();
}

/**
 * Display WiFi signal OK on screen
 * 
 * @param oled_screen_128_64 reference to Adafruit class
 * @param isVisible logo should be displayed
 */
void displaConnectedSignalWifi(Adafruit_SSD1306 &oled_screen_128_64, boolean isVisible = true) {
  int poxX = 112;
  int posY = 0;
  
  oled_screen_128_64.fillRect(poxX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);

  if (isVisible) {
    oled_screen_128_64.drawBitmap(poxX, posY, _ICONS_WIFI_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);  
  }
}

/**
 * Display WiFi no signal on screen
 * 
 * @param oled_screen_128_64 reference to Adafruit class
 * @param isVisible logo should be displayed
 */
void displaNotConnectedSignalWifi(Adafruit_SSD1306 &oled_screen_128_64, boolean isVisible = true) {
  int poxX = 112;
  int posY = 0;
  
  oled_screen_128_64.fillRect(poxX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);

  if (isVisible) {
    oled_screen_128_64.drawBitmap(poxX, posY, _ICONS_WIFI_NO_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
  }
}


/*
 * [PRIVATE METHODS]
 */
#endif //_OLED_DISPLAY_
