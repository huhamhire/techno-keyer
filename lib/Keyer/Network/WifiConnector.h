
#ifndef WIFI_CONNECTOR_H
#define WIFI_CONNECTOR_H

#include <Arduino.h>
#include <WiFi.h>

namespace TechnoKeyer {

    #define WIFI_RECONNECT_INTERVAL 30000   // 30s

    class WifiConnector {
    public:
        void connect();
        void checkStatus();

    private:
        bool _connected = false;
        unsigned long _connectTime = 0;

        const char* _ssid;
        const char* _password;
    };

    void vCheckWifi(void *pvParameters);
} // TechnoKeyer

#endif // WIFI_CONNECTOR_H
