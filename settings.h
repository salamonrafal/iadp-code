/**
 * @author Rafał Salamon <rafcio0584@gmail.com>
 */

#ifndef _SETTINGS_
#define _SETTINGS_

namespace Saltronix {
  namespace Settings {
    
    /**
     * Struct definition for oled display
     */
    struct _S_Def_Display_OLED {
      int mosi_pin;
      int sclk_pin;
      int dc_pin;
      unsigned int rst_pin;
      int cs_pin;
      int width;
      int height;
    };

    /**
     * Struct definition for sensors
     */
    struct _S_Def_Sensors {
      int dht_sensor_pin;
    };

    struct _S_Def_RTC {
      int sql_pin;
      int sda_pin;
    };

    /**
     * Struct definition for main settings
     */
    struct _S_Def_Settings {
      _S_Def_Display_OLED display_oled;
      _S_Def_Sensors sensors;
      _S_Def_RTC rtc;
    };
    
    /**
     * Create settings for oled display
     */
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
    
    /**
     * Create settings for sensors
     */
    _S_Def_Sensors createSensorsSettings() {
      struct _S_Def_Sensors S_Sensors;
      
      S_Sensors.dht_sensor_pin = 15;
    
      return S_Sensors;
    }

    /**
     * Create settings for RTC
     */
    _S_Def_RTC createRTCSettings() {
      struct _S_Def_RTC S_RTC;

      S_RTC.sda_pin = 21;
      S_RTC.sql_pin = 22;

      return S_RTC;
    }
    
    /**
     *  Create main struct wit app settings
     */
    _S_Def_Settings createMainSettings() {
      struct _S_Def_Settings S_Settings;
      
      S_Settings.display_oled = createDisplayOLEDSettings();
      S_Settings.sensors = createSensorsSettings();
      
      return S_Settings;
    }
  }
}

#endif //_SETTINGS_
