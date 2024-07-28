#ifndef _CLOCK_
#define _CLOCK_

#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

static const char* _ntpServer = "pool.ntp.org";
static const long _tzOffset = 8 * 3600;             // UTC+8
static unsigned long _updateInterval = 1800000;     // 30m

class NTPClock {
    private:
        NTPClient* _ntp;
    
    public:
        void begin();
        void syncTime();
        String getTimeString();
};

void vUpdateTime(void *pvParameters);

#endif  // _CLOCK_
