/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 */
#ifndef _SENSORS_DHT11_
#define _SENSORS_DHT11_

#include <DHTesp.h>

namespace Saltronix
{
  namespace Sensors {
    namespace DHT11 {
      TaskHandle_t tempTaskHandle = NULL;
      
      struct DHTSensorValue {
        double temperature;
        double humidity;
      };

      /**
       * Setup DHT sensor
       * 
       * @param dataPin data pin number on ESP32 board
       */
      DHTesp setupDHTSensor(int dataPin) {
        DHTesp dht;
        dht.setup(dataPin, DHTesp::DHT11);

        return dht;
      }

      /**
       * Get data from DHT sensor and convert to Struct
       * 
       * @param &dht reference to DHTesp class 
       */
      DHTSensorValue getDataFromDHTSensor(DHTesp &dht) {
        TempAndHumidity lastValues = dht.getTempAndHumidity();
        struct DHTSensorValue returnData;

        returnData.temperature = lastValues.temperature;
        returnData.humidity = lastValues.humidity;
        
        return returnData;
      }
    }
  }
}

#endif //_SENSORS_
