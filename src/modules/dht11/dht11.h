#ifndef _DHT11_H_
#define _DHT11_H_
#include <DHTesp.h>
#include "Ticker.h"
#include "models/models.h"

#define DHT_SENSOR_PIN 15

DHTesp dht;

TaskHandle_t tempTaskHandle = NULL;
Ticker tempTicker;
ComfortState cf;
bool tasksEnabled = false;
DHTSensrorValue stSensorDHTValue;

void tempTask(void *pvParameters);
bool getTemperature();
void triggerGetTemp();

bool setupDHT11() {
    dht.setup(DHT_SENSOR_PIN, DHTesp::DHT11);

    xTaskCreatePinnedToCore(
        tempTask,                       /* Function to implement the task */
        "tempTask ",                    /* Name of the task */
        4000,                           /* Stack size in words */
        NULL,                           /* Task input parameter */
        5,                              /* Priority of the task */
        &tempTaskHandle,                /* Task handle. */
        1
    );   

    if (tempTaskHandle == NULL) {
        Serial.println("Failed to start task for temperature update");
        return false;
    } else {
        // Start update of environment data every 20 seconds
        tempTicker.attach(20, triggerGetTemp);
    }

    return true;
}

/**
 * triggerGetTemp
 * Sets flag dhtUpdated to true for handling in loop()
 * called by Ticker getTempTimer
 */
void triggerGetTemp() {
  if (tempTaskHandle != NULL) {
	   xTaskResumeFromISR(tempTaskHandle);
  }
}

/**
 * Task to reads temperature from DHT11 sensor
 * @param pvParameters
 *    pointer to task parameters
 */
void tempTask(void *pvParameters) {
	Serial.println("tempTask loop started");

	while (1) // tempTask loop
    {
        if (tasksEnabled) {
            getTemperature();
        }

		vTaskSuspend(NULL);
    }
}


/**
 * getTemperature
 * Reads temperature from DHT11 sensor
 * @return bool
 *    true if temperature could be aquired
 *    false if aquisition failed
*/
bool getTemperature() {
	// Reading temperature for humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    TempAndHumidity newValues = dht.getTempAndHumidity();
	// Check if any reads failed and exit early (to try again).
	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return false;
	}

    stSensorDHTValue.humidity = newValues.humidity;
    stSensorDHTValue.temperature = newValues.temperature;
    
    String comfortStatus;

    switch(cf) {
        case Comfort_OK:
        comfortStatus = "Comfort_OK";
        break;
        case Comfort_TooHot:
        comfortStatus = "Comfort_TooHot";
        break;
        case Comfort_TooCold:
        comfortStatus = "Comfort_TooCold";
        break;
        case Comfort_TooDry:
        comfortStatus = "Comfort_TooDry";
        break;
        case Comfort_TooHumid:
        comfortStatus = "Comfort_TooHumid";
        break;
        case Comfort_HotAndHumid:
        comfortStatus = "Comfort_HotAndHumid";
        break;
        case Comfort_HotAndDry:
        comfortStatus = "Comfort_HotAndDry";
        break;
        case Comfort_ColdAndHumid:
        comfortStatus = "Comfort_ColdAndHumid";
        break;
        case Comfort_ColdAndDry:
        comfortStatus = "Comfort_ColdAndDry";
        break;
        default:
        comfortStatus = "Unknown:";
        break;
    };
	return true;
}
#endif