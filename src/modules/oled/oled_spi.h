#ifndef _OLED_SPI_H_
#define _OLED_SPI_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "consts/icons.h"
#include "consts/images.h"
#include "consts/translations.h"

#define OLED_SPI_FONT_SIZE 7
#define OLED_SPI_PIN_MOSI 23
#define OLED_SPI_PIN_SCLK 18
#define OLED_SPI_PIN_DC 19
#define OLED_SPI_PIN_RST -1
#define OLED_SPI_PIN_CS 5
#define OLED_SPI_WIDTH 128
#define OLED_SPI_HEIGHT 64
#define OLED_SPI_TOP_LINES 16
#define OLED_SPI_BOTTOM_Lines 48

Adafruit_SSD1306 oled_screen_128_64 (
    OLED_SPI_WIDTH,
    OLED_SPI_HEIGHT,
    OLED_SPI_PIN_MOSI,
    OLED_SPI_PIN_SCLK,
    OLED_SPI_PIN_DC,
    OLED_SPI_PIN_RST,
    OLED_SPI_PIN_CS
);

void __printBlockTitle(int posX,  int posY, int blockWidth, const char txTitle[]);
void __displayTemperature(int posX,  int posY, int blockWidth, float dValue);
void __displayHumidity(int posX,  int posY, int blockWidth, float dValue);
void __displayWaterLevel(int posX,  int posY, int blockWidth, boolean isToLow);

/**
 * Initial OLED display
 */
void setupDisplayOLED() {
    oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
    oled_screen_128_64.clearDisplay();

    oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
    oled_screen_128_64.clearDisplay();

    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(WHITE);
}

/**
 * Drawing on blue screen grid (bottom color screen)
 */
void drawGrid() {
    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.drawFastHLine(0, OLED_SPI_TOP_LINES, OLED_SPI_WIDTH, WHITE);
    oled_screen_128_64.drawFastVLine(OLED_SPI_HEIGHT, OLED_SPI_TOP_LINES, OLED_SPI_BOTTOM_Lines, WHITE);
}

/**
 * Drawing on yellow screen current date (top color screen)
 * 
 * @param chDate[11] current date to display max 10 chars
 */
void printDate (char chDate[11]) {
    int posX = 0;
    int posY = 0;
    
    oled_screen_128_64.fillRect(posX, posY, 60, OLED_SPI_FONT_SIZE, BLACK);
    oled_screen_128_64.setCursor(posX, posY);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(WHITE);
    oled_screen_128_64.print(chDate);
}

/**
 * Drawing on yellow screen current time
 * 
 * @param chTime[6] current time to display max 5 chars
 */
void printTime(char chTime[6]) {
    int posX = 30;
    int posY = 9;
    
    oled_screen_128_64.fillRect(posX, posY, 29, OLED_SPI_FONT_SIZE, BLACK);
    oled_screen_128_64.setCursor(posX, posY);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(WHITE);
    oled_screen_128_64.print(chTime);
}

/**
 * Display WiFi signal OK on screen
 * 
 * @param isVisible logo should be displayed
 */
void displayConnectedSignalWifi(boolean isVisible = true) {
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
 * @param isVisible logo should be displayed
 */
void displayNotConnectedSignalWifi(boolean isVisible = true) {
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
 * @param dTemperature current temperature in room
 * @param dHumidity current humidity in room
 */
void displayLeftColumne(float dTemperature = 0.0, float dHumidity = 0) {
    int posX = 1;
    int posY = 18;
    int blockWidth = 62;
    int blockHeight = 45;
    
    oled_screen_128_64.fillRect(posX, posY, blockWidth, blockHeight, BLACK);
    oled_screen_128_64.setCursor(posX, posY);
    __printBlockTitle(posX, posY, blockWidth, _T_PL_ROOM);
    __displayTemperature(posX, posY, blockWidth, dTemperature);
    __displayHumidity(posX, posY, blockWidth, dHumidity);
}

/**
 * Display left col with information about aquarium
 * 
 * @param dTemperature current temperature in aquarium
 * @param waterIsToLow current flag whater level in aquarium
 */
void displayRightColumne(float dTemperature = 0.0, boolean waterIsToLow = false) {
    int posX = 66;
    int posY = 18;
    int blockWidth = 61;
    int blockHeight = 45;
    
    oled_screen_128_64.fillRect(posX, posY, blockWidth, blockHeight, BLACK);
    oled_screen_128_64.setCursor(posX, posY);
    __printBlockTitle(posX, posY, blockWidth, _T_PL_AQUA);
    __displayTemperature(posX, posY, blockWidth, dTemperature);
    __displayWaterLevel(posX, posY, blockWidth, waterIsToLow);
}

/**
 * Display splash screen
 */
void displaySplashScreen() {
    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.drawBitmap(0, 16, _IMAGE_LOGO_SPLASH, _IMAGES_SIZE_SPLASH_WIDTH, _IMAGES_SIZE_SPLASH_HEIGHT, 1);
}

/**
 * Display all elements on OLED screen
 */
void displayAllOnScreen() {
    oled_screen_128_64.display();
}

void clearAllOnScreen() {
    oled_screen_128_64.clearDisplay();
}

/**
 * Drwaing block title
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param txTitle title
 */
void __printBlockTitle(int posX,  int posY, int blockWidth, const char txTitle[]) {
    int margin = 2;

    oled_screen_128_64.fillRect(posX, posY, blockWidth, OLED_SPI_FONT_SIZE + (2 * margin), WHITE);
    oled_screen_128_64.setCursor(posX + margin, posY + margin);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(BLACK);
    oled_screen_128_64.print(txTitle);
}

/**
 * Drawing current temperature
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param dValue temperature value
 */
void __displayTemperature(int posX,  int posY, int blockWidth, float dValue) {
    int topMargin = 12;
    int leftMargin = 6;
    int posYMargin = posY + topMargin;
    int posXMargin = posX + leftMargin;
    
    oled_screen_128_64.drawBitmap(posXMargin, posY + topMargin, _ICONS_THERMOMETER_16x16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
    oled_screen_128_64.setCursor(posXMargin + 17, posYMargin);
    oled_screen_128_64.setTextSize(2);
    oled_screen_128_64.setTextColor(WHITE);
    oled_screen_128_64.print((uint8_t) dValue);
}

/**
 * Drawing current temperature
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param dValue humidity value
 */
void __displayHumidity(int posX,  int posY, int blockWidth, float dValue) {
    int topMargin = 30;
    int leftMargin = 6;
    int posYMargin = posY + topMargin;
    int posXMargin = posX + leftMargin;


    oled_screen_128_64.drawBitmap(posXMargin, posY+topMargin, _ICONS_HUMIDITY_16x16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
    oled_screen_128_64.setCursor(posXMargin + 17, posYMargin);
    oled_screen_128_64.setTextSize(2);
    oled_screen_128_64.setTextColor(WHITE);
    oled_screen_128_64.printf("%d%%", (int) dValue);
}

 /**
 * Drawing current wather level
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param isToLow flag water is to low
 */
void __displayWaterLevel(int posX,  int posY, int blockWidth, boolean isToLow) {
    int topMargin = 30;
    int leftMargin = (blockWidth - 16) / 2;
    int posYMargin = posY + topMargin;
    int posXMargin = posX + leftMargin;

    if (isToLow == true) {
        oled_screen_128_64.drawBitmap(posXMargin, posYMargin, _ICONS_WATER_LEVEL_LOW, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
    } else {
        oled_screen_128_64.drawBitmap(posXMargin, posYMargin, _ICONS_WATER_LEVEL_HIGH, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
    }
}

  

#endif