#ifndef _KEYER_WIFI_
#define _KEYER_WIFI_

#include <Wifi.h>

#ifndef STA_SSID
#define STA_SSID "SSID"
#define STA_PSK "password"
#endif

#define WIFI_CHECK_INTERVAL 1000  // 1s
#define WIFI_RECO_INTERVAL 30000  // 30s

class KeyerWifi {
    private:
        static KeyerWifi* instance;

        const char* ssid;
        const char* password;

        unsigned long prev_ms;
        unsigned long prev_connect_ms;
        bool connected;

    public:
        KeyerWifi();

        static KeyerWifi* getInstance();

        void connect();
        void check();
};

extern KeyerWifi wifiClient;

#endif  // _KEYER_WIFI_
