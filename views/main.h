/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 */

#ifndef _VIEWS_MAIN_
#define _VIEWS_MAIN_

#include "oled_display.h"
#include "sensors.h"

using namespace Saltronix::OLED_Display;
using namespace Saltronix::Sensor_DHT11;

namespace Saltronix {
    namespace Views {

        /**
         * Drawing home screen on OLED display
         * 
         * @param &oled_screen_128_64 reference to Adafruit class 
         * @param cDate current date from RTC
         * @param cTime current time from RTC
         * @param DHTSensorData data read from DHT11 sensor
         * @param dAquariumTemperature temperatur read from sensor
         * @param bWaterLevel status read from sensor
         * @param bWifiConnected WiFi networ status
         * 
         */
        void drawMainPage (
            Adafruit_SSD1306 &oled_screen_128_64,
            char cDate[],
            char cTime[],
            DHTSensorValue DHTSensorData,
            double dAquariumTemperature,
            bool bWaterLevel,
            bool bWifiConnected
        ) {
            if (bWifiConnected) 
                displayConnectedSignalWifi(oled_screen_128_64);
            else
                displayNotConnectedSignalWifi(oled_screen_128_64);

            displayLeftColumne(oled_screen_128_64, DHTSensorData.temperature, DHTSensorData.humidity);
            displayRightColumne(oled_screen_128_64, dAquariumTemperature, bWaterLevel);
            
            printDate(oled_screen_128_64, cDate);
            printTime(oled_screen_128_64, cTime);
        }
        
    }
}
#endif // _VIEWS_MAIN_