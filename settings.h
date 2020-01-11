#ifndef _SETTINGS_
#define _SETTINGS_

namespace Saltronix {
  namespace Settings {
    #include "settings_def.h"
    
    _S_Def_Display_OLED createDisplayOLEDSettings() {
      struct _S_Def_Display_OLED S_Display_OLED;
      
      S_Display_OLED.mosi_pin = 23;
      S_Display_OLED.sclk_pin = 18;
      S_Display_OLED.dc_pin = 19;
      S_Display_OLED.rst_pin = -1;
      S_Display_OLED.cs_pin = 5;
      S_Display_OLED.width = 128;
      S_Display_OLED.height = 64;
      
      return S_Display_OLED;
    }
    
    _S_Def_Sensors createSensorsSettings() {
      struct _S_Def_Sensors S_Sensors;
      
      S_Sensors.dht_sensor_pin = 15;
    
      return S_Sensors;
    }
    
    _Def_Settings createMainSettings() {
      struct _Def_Settings S_Settings;
      
      S_Settings.display_oled = createDisplayOLEDSettings();
      S_Settings.sensors = createSensorsSettings();
      
      return S_Settings;
    }
  }
}

#endif //_SETTINGS_
