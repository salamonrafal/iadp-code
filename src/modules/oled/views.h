#ifndef _OLED_SPI_VIEWS_H_
#define _OLED_SPI_VIEWS_H_
#include "modules/oled/oled_spi.h"
#include "models/models.h"

void showMainView(
    char chDate[],
    char chTime[],
    double dAquariumTemperature, 
    boolean bIsWatherLevelToLow, 
    DHTSensrorValue stSensorData, 
    bool bIsWifiConnected
) {
    clearAllOnScreen();
    drawGrid();
    displayLeftColumne(stSensorData.temperature, stSensorData.humidity);
    displayRightColumne(dAquariumTemperature, bIsWatherLevelToLow);
    printDate(chDate);
    printTime(chTime);
    
    if (bIsWifiConnected)
        displayConnectedSignalWifi();
    else
        displayNotConnectedSignalWifi();

    displayAllOnScreen();
}

#endif