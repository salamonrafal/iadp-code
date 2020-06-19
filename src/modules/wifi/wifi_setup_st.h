#ifndef _WIFI_SETUP_ST_H_
#define _WIFI_SETUP_ST_H_

typedef struct st_wifi_setup {
    float temperature = 0;
    float humidity = 0;
    char ping[5];

    void (*run_motor_call)      (unsigned int motorType, unsigned int motorDirection);
    void (*set_alarm_call)      (unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minutes);
    void (*set_self_test_call)  (unsigned int time);

} Wifi_Setup_T;

typedef void (*run_motor_call_t)    (unsigned int motorType, unsigned int motorDirection);
typedef void (*set_alarm_call_t)    (unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minutes);
typedef void (*set_self_test_call_t) (unsigned int time);

#endif