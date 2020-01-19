#ifndef _RTC_MODULE_H_
#define _RTC_MODULE_H_

#define countof(a) (sizeof(a) / sizeof(a[0]))

#include <Wire.h> // must be included here so that Arduino library object file references work
#include <RtcDS3231.h>

RtcDS3231<TwoWire> Rtc(Wire);
char chRtcDateValue[11] = "19.01.2020";
char chRtcTimeValue[6] = "00:00";

/**
 * Setup RTC module
 */
void setupRTCModule() {
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    if (!Rtc.IsDateTimeValid()) {
        if (Rtc.LastError() != 0) {
            Serial.print("see https://www.arduino.cc/en/Reference/WireEndTransmission for  RTC communications error = ");
            Serial.println(Rtc.LastError());
        } else {
            Serial.println("RTC lost confidence in the DateTime!");
            Rtc.SetDateTime(compiled);
        }
    }

    if (!Rtc.GetIsRunning()) {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();

    if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("RTC is newer than compile time. (this is expected)");
    } else if (now == compiled) {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    Rtc.Enable32kHzPin(false);
    Rtc.SetSquareWavePin(DS3231SquareWavePin_ModeNone); 
}

/**
 * Get Date & Time from RTC
 */
void getDateTimeFromRTCModule()
{
    if (!Rtc.IsDateTimeValid()) {
        if (Rtc.LastError() != 0) {
            Serial.print("RTC communications error = ");
            Serial.println(Rtc.LastError());
        } else {
            Serial.println("RTC lost confidence in the DateTime!");
        }
    }

    RtcDateTime nowDateTime = Rtc.GetDateTime();

    snprintf_P(
        chRtcDateValue, 
        countof(chRtcDateValue),
        PSTR("%02u/%02u/%04u"),
        nowDateTime.Month(),
        nowDateTime.Day(),
        nowDateTime.Year()
    );

    snprintf_P(
        chRtcTimeValue, 
        countof(chRtcTimeValue),
        PSTR("%02u:%02u"),
        nowDateTime.Hour(),
        nowDateTime.Minute()
    );
}

#endif // _RTC_MODULE_H_ 