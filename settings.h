#ifndef _SETTINGS_
#define _SETTINGS_

#include "settings_def.h"

struct _S_Def_Display_OLED S_Display_OLED;
struct _Def_Settings S_Settings;

_S_Def_Display_OLED createDisplayOLEDSettings() {
  S_Display_OLED.mosi_pin = 23;
  S_Display_OLED.sclk_pin = 18;
  S_Display_OLED.dc_pin = 19;
  S_Display_OLED.rst_pin = -1;
  S_Display_OLED.cs_pin = 5;
  S_Display_OLED.width = 128;
  S_Display_OLED.height = 64;
  
  return S_Display_OLED;
}

_Def_Settings createMainSettings() {
  S_Settings.display_oled = createDisplayOLEDSettings();
  
  return S_Settings;
}

#endif //_SETTINGS_
