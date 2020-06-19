#ifndef _OLED_SPI_H_
#define _OLED_SPI_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "consts/icons.h"
#include "consts/images.h"
#include "consts/translations.h"

#define OLED_SPI_FONT_SIZE 7
#define OLED_SPI_FONT_SIZE_MIN 6
#define OLED_SPI_PIN_MOSI 23
#define OLED_SPI_PIN_SCLK 18
#define OLED_SPI_PIN_DC 19
#define OLED_SPI_PIN_RST -1
#define OLED_SPI_PIN_CS 5
#define OLED_SPI_WIDTH 128
#define OLED_SPI_HEIGHT 64
#define OLED_SPI_TOP_LINES 16
#define OLED_SPI_BOTTOM_Lines 48
#define EFFECTS_FADE_DELAY 50

Adafruit_SSD1306 oled_screen_128_64 (
    OLED_SPI_WIDTH,
    OLED_SPI_HEIGHT,
    OLED_SPI_PIN_MOSI,
    OLED_SPI_PIN_SCLK,
    OLED_SPI_PIN_DC,
    OLED_SPI_PIN_RST,
    OLED_SPI_PIN_CS
);

typedef enum  
{
    EFFECT_FADEIN = 0,
    EFFECT_FADEOUT = 1
} ScreenEfects_t;

void __printBlockTitle(int posX,  int posY, int blockWidth, const char txTitle[]);
void __displayTemperature(int posX,  int posY, int blockWidth, float dValue);
void __displayHumidity(int posX,  int posY, int blockWidth, float dValue);
void __displayWaterLevel(int posX,  int posY, int blockWidth, boolean isToLow);
void printText(const char text[], int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx);
void printText(char text[], int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx);
void printText(String sText, int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx);
void fade_effect(ScreenEfects_t effect, boolean a);
void __fade_in_dim(uint8_t c, uint8_t v, int s, boolean a);
void __fade_out_dim(uint8_t c, uint8_t v, int s, boolean a);

/**
 * @brief Initial OLED display
 */
void setupDisplayOLED() 
{
    oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
    oled_screen_128_64.clearDisplay();

    oled_screen_128_64.begin(SSD1306_SWITCHCAPVCC);
    oled_screen_128_64.clearDisplay();

    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(WHITE);
}

/**
 * @brief Drawing on blue screen grid (bottom color screen)
 */
void drawGrid() 
{
    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.drawFastHLine(0, OLED_SPI_TOP_LINES, OLED_SPI_WIDTH, WHITE);
    oled_screen_128_64.drawFastVLine(OLED_SPI_HEIGHT, OLED_SPI_TOP_LINES, OLED_SPI_BOTTOM_Lines, WHITE);
}

/**
 * @brief Drawing on yellow screen current date (top color screen)
 * 
 * @param chDate[11] current date to display max 10 chars
 */
void printDate (char chDate[11]) 
{
    int posX = 0;
    int posY = 0;
    
    printText(chDate, posX, posY, 60, OLED_SPI_FONT_SIZE, SSD1306_BLACK, SSD1306_WHITE);
}

/**
 * @brief Drawing on yellow screen current time
 * 
 * @param chTime[6] current time to display max 5 chars
 */
void printTime(char chTime[6]) 
{
    int posX = 30;
    int posY = 9;
    
    printText(chTime, posX, posY, 29, OLED_SPI_FONT_SIZE, SSD1306_BLACK, SSD1306_WHITE);
}

/**
 * @brief Display label for connection with network
 * 
 * @param char chText[16] 
 */
void prinConnecting(const char chText[16])
{
    int posX = 38;
    int posY = 9;

    printText(chText, posX, posY, 29, OLED_SPI_FONT_SIZE, SSD1306_BLACK, SSD1306_WHITE);
}

/**
 * @brief Print when initilize machine
 * 
 * @param String sText 
 */
void printInitText(String sText)
{
    int posX = 2;
    int posY = 2;

    printText(sText, posX, posY, 126, OLED_SPI_FONT_SIZE_MIN, SSD1306_BLACK, SSD1306_WHITE);
}

/**
 * @brief Print text on oled screen base on SSD1306 for 128x64 screen size
 * 
 * @param text[]
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param c_bg 
 * @param c_tx 
 */
void printText(const char text[], int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx)
{
    oled_screen_128_64.fillRect(x, y, w, h, c_bg);
    oled_screen_128_64.setCursor(x, y);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(c_tx);
    oled_screen_128_64.print(text);
}

/**
 * @brief Print text on oled screen base on SSD1306 for 128x64 screen size
 * 
 * @param text[]
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param c_bg 
 * @param c_tx 
 */
void printText(char text[], int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx)
{
    oled_screen_128_64.fillRect(x, y, w, h, c_bg);
    oled_screen_128_64.setCursor(x, y);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(c_tx);
    oled_screen_128_64.print(text);
}

/**
 * @brief Print text on oled screen base on SSD1306 for 128x64 screen size
 * 
 * @param sText
 * @param x 
 * @param y 
 * @param w 
 * @param h 
 * @param c_bg 
 * @param c_tx 
 */
void printText(String sText, int x, int y, int w, int h, uint16_t c_bg, uint16_t c_tx)
{
    oled_screen_128_64.fillRect(x, y, w, h, c_bg);
    oled_screen_128_64.setCursor(x, y);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(c_tx);
    oled_screen_128_64.print(sText);
}

/**
 * @brief Display WiFi signal OK on screen
 * 
 * @param isVisible logo should be displayed
 */
void displayConnectedSignalWifi(boolean isVisible = true) 
{
    int posX = 112;
    int posY = 0;
    
    oled_screen_128_64.fillRect(posX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);

    if (isVisible) {
        oled_screen_128_64.drawBitmap(posX, posY, _ICONS_WIFI_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);  
    }
}

/**
 * @brief Display WiFi no signal on screen
 * 
 * @param isVisible logo should be displayed
 */
void displayNotConnectedSignalWifi(boolean isVisible = true) 
{
    int posX = 112;
    int posY = 0;
    
    oled_screen_128_64.fillRect(posX, posY, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, BLACK);

    if (isVisible) {
        oled_screen_128_64.drawBitmap(posX, posY, _ICONS_WIFI_NO_SIGNAL_16X16, _ICONS_SIZE_TOP_WIDTH, _ICONS_SIZE_TOP_HEIGHT, 1);
    }
}

/**
 * @brief Display left col with information about room
 * 
 * @param dTemperature current temperature in room
 * @param dHumidity current humidity in room
 */
void displayLeftColumne(float dTemperature = 0.0, float dHumidity = 0) 
{
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
 * @brief Display left col with information about aquarium
 * 
 * @param dTemperature current temperature in aquarium
 * @param waterIsToLow current flag whater level in aquarium
 */
void displayRightColumne(float dTemperature = 0.0, boolean waterIsToLow = false) 
{
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
 * @brief Display splash screen
 */
void displaySplashScreen() 
{
    oled_screen_128_64.clearDisplay();
    oled_screen_128_64.drawBitmap(0, 16, _IMAGE_LOGO_SPLASH, _IMAGES_SIZE_SPLASH_WIDTH, _IMAGES_SIZE_SPLASH_HEIGHT, 1);
}

/**
 * @brief Display all elements on OLED screen
 */
void displayAllOnScreen() 
{
    oled_screen_128_64.display();
}

/**
 * @brief Remove everything from screen and displa blank
 * 
 */
void clearAllOnScreen() 
{
    oled_screen_128_64.clearDisplay();
}

/**
 * @brief Drwaing block title
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param txTitle title
 */
void __printBlockTitle(int posX,  int posY, int blockWidth, const char txTitle[]) 
{
    int margin = 2;

    oled_screen_128_64.fillRect(posX, posY, blockWidth, OLED_SPI_FONT_SIZE + (2 * margin), WHITE);
    oled_screen_128_64.setCursor(posX + margin, posY + margin);
    oled_screen_128_64.setTextSize(1);
    oled_screen_128_64.setTextColor(BLACK);
    oled_screen_128_64.print(txTitle);
}

/**
 * @brief Drawing current temperature
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param dValue temperature value
 */
void __displayTemperature(int posX,  int posY, int blockWidth, float dValue) 
{
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
 * @brief Drawing current temperature
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param dValue humidity value
 */
void __displayHumidity(int posX,  int posY, int blockWidth, float dValue) 
{
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
 * @brief Drawing current wather level
 * 
 * @param posX start drawing on X vector
 * @param posY start drawing on Y vector
 * @param blockWidth current block width
 * @param isToLow flag water is to low
 */
void __displayWaterLevel(int posX,  int posY, int blockWidth, boolean isToLow) 
{
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

/**
 * @brief Screen oled fade effects
 * 
 * @param effect Enum efects type
 * @param a Turn off / on animation
 */
void fade_effect(ScreenEfects_t effect, boolean a = true)
{
    uint8_t dim1_max = 157;
    uint8_t dim2_max = 34;
    uint8_t dim1_step = 10;
    uint8_t dim2_step = 17;

    uint8_t dim1_cmd = 0x81;
    uint8_t dim2_cmd = 0xD9;

    switch (effect)
    {
        case ScreenEfects_t::EFFECT_FADEIN:
            __fade_in_dim(dim1_cmd, dim1_max, dim1_step, a);
            __fade_in_dim(dim2_cmd, dim2_max, 17, a);
            break;

        case ScreenEfects_t::EFFECT_FADEOUT:
        default:
            __fade_out_dim(dim1_cmd, dim1_max, dim1_step, a);
            __fade_out_dim(dim2_cmd, dim2_max, dim2_step, a);
            break;
    }
}

/**
 * @brief Fade in effect for oled screen
 * 
 * @param c Command
 * @param v Max value
 * @param s Increment index step
 * @param a Turn off / on animation
 */
void __fade_in_dim(uint8_t c, uint8_t v, int s, boolean a = true)
{
    if (a) {
        for (int dim = 0; dim <= v; dim += s) {
            oled_screen_128_64.ssd1306_command(c);
            oled_screen_128_64.ssd1306_command(dim);
            delay(EFFECTS_FADE_DELAY);
        }
    } else {
        oled_screen_128_64.ssd1306_command(c);
        oled_screen_128_64.ssd1306_command(v);
    }
}

/**
 * @brief Fade out effect for oled screen
 * 
 * @param c Command
 * @param v Start value
 * @param s Decrement index step
 * @param a Turn off / on animation
 */
void __fade_out_dim(uint8_t c, uint8_t v, int s, boolean a = true)
{
    if (a) {
        for (int dim = v; dim >= 0; dim -= s) {
            oled_screen_128_64.ssd1306_command(c);
            oled_screen_128_64.ssd1306_command(dim);
            delay(EFFECTS_FADE_DELAY);
        }
    } else {
        oled_screen_128_64.ssd1306_command(c);
        oled_screen_128_64.ssd1306_command(0);
    }
}

#endif