#include <Clock.h>

void NTPClock::begin() {
    WiFiUDP _udp;
    _ntp = new NTPClient(_udp);
    _ntp->setPoolServerName(_ntpServer);
    _ntp->setTimeOffset(_tzOffset);
    _ntp->setUpdateInterval(_updateInterval);
    _ntp->begin();
}

// Sync time
void NTPClock::syncTime() {
    _ntp->update();
}

// Get time string
String NTPClock::getTimeString() {
    return _ntp->getFormattedTime();
}

// Task to update time
void vUpdateTime(void *pvParameters) {
    NTPClock* ntpClock = (NTPClock*)pvParameters;
    for (;;) {
        // ntpClock->syncTime();
        Serial.println(ntpClock->getTimeString());

        // Check every 1 minute
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
