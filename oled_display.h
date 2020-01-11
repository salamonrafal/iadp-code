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
#include "images.h"

/*
 * CONST
 */
#define OLED_FONT_SIZE 7

namespace Saltronix {
  namespace OLED_Display {
    /*
     * [PRIVATE METHODS]
     */
    
    /**
     * Drwaing block title
     * 
     * @param oled_screen_128_64 reference to Adafruit class 
     * @param posX start drawing on X vector
     * @param posY start drawing on Y vector
     * @param blockWidth current block width
     * @param txTitle title
     */
    void __printBlockTitle(Adafruit_SSD1306 &oled_screen_128_64, int posX,  int posY, int blockWidth, const char txTitle[]) {
      int margin = 2;
      oled_screen_128_64.fillRect(posX, posY, blockWidth, OLED_FONT_SIZE+margin+margin, WHITE);
      oled_screen_128_64.setCursor(posX+margin, posY+margin);
      oled_screen_128_64.setTextSize(1);
      oled_screen_128_64.setTextColor(BLACK);
      oled_screen_128_64.print(txTitle);
    }
    
    /**
     * Drwaing block title
     * 
     * @param oled_screen_128_64 reference to Adafruit class 
     * @param posX start drawing on X vector
     * @param posY start drawing on Y vector
     * @param blockWidth current block width
     * @param txTitle title
     */
    void __printBlockTitle(Adafruit_SSD1306 &oled_screen_128_64, int posX,  int posY, int blockWidth, char txTitle[]) {
      int margin = 2;
      oled_screen_128_64.fillRect(posX, posY, blockWidth, OLED_FONT_SIZE+margin+margin, WHITE);
      oled_screen_128_64.setCursor(posX+margin, posY+margin);
      oled_screen_128_64.setTextSize(1);
      oled_screen_128_64.setTextColor(BLACK);
      oled_screen_128_64.print(txTitle);
    }
    
    /**
     * Drawing current temperature
     * 
     * @param oled_screen_128_64 reference to Adafruit class 
     * @param posX start drawing on X vector
     * @param posY start drawing on Y vector
     * @param blockWidth current block width
     * @param dValue temperature value
     */
    void __displayTemperature(Adafruit_SSD1306 &oled_screen_128_64, int posX,  int posY, int blockWidth, double dValue) {
      int topMargin = 12;
      int leftMargin = 6;
      int posYMargin = posY+topMargin;
      int posXMargin = posX+leftMargin;
      
      oled_screen_128_64.drawBitmap(posXMargin, posY+topMargin, _ICONS_THERMOMETER_16x16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
      oled_screen_128_64.setCursor(posXMargin+17, posY+topMargin);
      oled_screen_128_64.setTextSize(2);
      oled_screen_128_64.setTextColor(WHITE);
      oled_screen_128_64.print((uint8_t) dValue);
    }
    
    /**
     * Drawing current temperature
     * 
     * @param oled_screen_128_64 reference to Adafruit class 
     * @param posX start drawing on X vector
     * @param posY start drawing on Y vector
     * @param blockWidth current block width
     * @param dValue humidity value
     */
    void __displayHumidity(Adafruit_SSD1306 &oled_screen_128_64, int posX,  int posY, int blockWidth, double dValue) {
      int topMargin = 30;
      int leftMargin = 6;
      int posYMargin = posY+topMargin;
      int posXMargin = posX+leftMargin;
    
    
      oled_screen_128_64.drawBitmap(posXMargin, posY+topMargin, _ICONS_HUMIDITY_16x16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
      oled_screen_128_64.setCursor(posXMargin+17, posY+topMargin);
      oled_screen_128_64.setTextSize(2);
      oled_screen_128_64.setTextColor(WHITE);
      oled_screen_128_64.printf("%d%%", (int) dValue);
    }
    
    /**
     * Drawing current wather level
     * 
     * @param oled_screen_128_64 reference to Adafruit class 
     * @param posX start drawing on X vector
     * @param posY start drawing on Y vector
     * @param blockWidth current block width
     * @param isToLow flag water is to low
     */
    void __displayWaterLevel(Adafruit_SSD1306 &oled_screen_128_64, int posX,  int posY, int blockWidth, boolean isToLow) {
      int topMargin = 30;
      int leftMargin = (blockWidth-16)/2;
      int posYMargin = posY+topMargin;
      int posXMargin = posX+leftMargin;
    
      if (isToLow == true) {
        oled_screen_128_64.drawBitmap(posXMargin, posY+topMargin, _ICONS_WATER_LEVEL_LOW, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
      } else {
        oled_screen_128_64.drawBitmap(posXMargin, posY+topMargin, _ICONS_WATER_LEVEL_HIGH, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
      }
    }
    
    
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
      oled_screen_128_64.clearDisplay();
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
      int posX = 0;
      int posY = 0;
      
      oled_screen_128_64.fillRect(posX, posY, 60, OLED_FONT_SIZE, BLACK);
      oled_screen_128_64.setCursor(posX, posY);
      oled_screen_128_64.setTextSize(1);
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
      int posX = 30;
      int posY = 9;
      
      oled_screen_128_64.fillRect(posX, posY, 29, OLED_FONT_SIZE, BLACK);
      oled_screen_128_64.setCursor(posX, posY);
      oled_screen_128_64.setTextSize(1);
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
    void displayConnectedSignalWifi(Adafruit_SSD1306 &oled_screen_128_64, boolean isVisible = true) {
      int posX = 112;
      int posY = 0;
      
      oled_screen_128_64.fillRect(posX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);
    
      if (isVisible) {
        oled_screen_128_64.drawBitmap(posX, posY, _ICONS_WIFI_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);  
      }
    }
    
    /**
     * Display WiFi no signal on screen
     * 
     * @param oled_screen_128_64 reference to Adafruit class
     * @param isVisible logo should be displayed
     */
    void displayNotConnectedSignalWifi(Adafruit_SSD1306 &oled_screen_128_64, boolean isVisible = true) {
      int posX = 112;
      int posY = 0;
      
      oled_screen_128_64.fillRect(posX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);
    
      if (isVisible) {
        oled_screen_128_64.drawBitmap(posX, posY, _ICONS_WIFI_NO_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
      }
    }
    
    /**
     * Display left col with information about room
     * 
     * @param oled_screen_128_64 reference to Adafruit class
     * @param dTemperature current temperature in room
     * @param dHumidity current humidity in room
     */
    void displayLeftColumne(Adafruit_SSD1306 &oled_screen_128_64, double dTemperature = 0.0, double dHumidity = 0) {
      int posX = 1;
      int posY = 18;
      int blockWidth = 62;
      int blockHeight = 45;
      
      oled_screen_128_64.fillRect(posX, posY, blockWidth, blockHeight, BLACK);
      oled_screen_128_64.setCursor(posX, posY);
      __printBlockTitle(oled_screen_128_64, posX, posY, blockWidth, _T_PL_ROOM);
      __displayTemperature(oled_screen_128_64, posX, posY, blockWidth, dTemperature);
      __displayHumidity(oled_screen_128_64, posX, posY, blockWidth, dHumidity);
    }
    
    /**
     * Display left col with information about aquarium
     * 
     * @param oled_screen_128_64 reference to Adafruit class
     * @param dTemperature current temperature in aquarium
     * @param waterIsToLow current flag whater level in aquarium
     */
    void displayRightColumne(Adafruit_SSD1306 &oled_screen_128_64, double dTemperature = 0.0, boolean waterIsToLow = false) {
      int posX = 66;
      int posY = 18;
      int blockWidth = 61;
      int blockHeight = 45;
      
      oled_screen_128_64.fillRect(posX, posY, blockWidth, blockHeight, BLACK);
      oled_screen_128_64.setCursor(posX, posY);
      __printBlockTitle(oled_screen_128_64, posX, posY, blockWidth, _T_PL_AQUA);
      __displayTemperature(oled_screen_128_64, posX, posY, blockWidth, dTemperature);
      __displayWaterLevel(oled_screen_128_64, posX, posY, blockWidth, waterIsToLow);
    }
    
    /**
     * Display splash screen
     * 
     * @param oled_screen_128_64 reference to Adafruit class
     */
    void displaySplashScreen(Adafruit_SSD1306 &oled_screen_128_64) {
      oled_screen_128_64.clearDisplay();
      oled_screen_128_64.drawBitmap(0, 16, _IMAGE_LOGO_SPLASH, _IMAGES_SIZE_SPLASH_WIDTH, _IMAGES_SIZE_SPLASH_HEIGHT, 1);
      oled_screen_128_64.display();
    }
  }
}

#endif //_OLED_DISPLAY_
