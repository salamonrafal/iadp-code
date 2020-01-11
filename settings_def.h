#ifndef _SETTINGS_DEF_
#define _SETTINGS_DEF_

struct _S_Def_Display_OLED {
  int mosi_pin;
  int sclk_pin;
  int dc_pin;
  unsigned int rst_pin;
  int cs_pin;
  int width;
  int height;
};

struct _S_Def_Sensors {
  int dht_sensor_pin;
};

struct _Def_Settings {
  _S_Def_Display_OLED display_oled;
  _S_Def_Sensors sensors;
};

#endif //_SETTINGS_DEF_
