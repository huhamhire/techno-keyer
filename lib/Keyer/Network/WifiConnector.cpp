
#include "WifiConnector.h"

namespace TechnoKeyer {
    /**
     * Connect to WiFi
     */
    void WifiConnector::connect() {
        if (_connected) {
            // Already connected
            return;
        }

        _connectTime = millis();

        if (strlen(_ssid) == 0 || strlen(_password) == 0) {
            Serial.println("WIFI SSID or password not set");
            return;
        }

        // Start new connection
        Serial.println("WIFI connecting to: " + String(_ssid));

        WiFiClass::mode(WIFI_STA);
        WiFi.begin(_ssid, _password);
    }

    /**
     * Check WiFi connection status
     */
    void WifiConnector::checkStatus() {
        if (WiFiClass::status() == WL_CONNECTED && !_connected) {
            // New connection
            _connected = true;
            String ip = WiFi.localIP().toString();

            char msg[100];
            sprintf(msg, "WIFI connected: %s, IP: %s", _ssid, ip.c_str());
            Serial.println(msg);
        } else if (WiFiClass::status() != WL_CONNECTED && _connected) {
            // Disconnect
            _connected = false;
            Serial.println("WIFI disconnected");
        }

        // Auto reconnect
        unsigned long now = millis();
        if (now - _connectTime > WIFI_RECONNECT_INTERVAL && WiFiClass::status() != WL_CONNECTED) {
            WiFi.disconnect();
            connect();
        }
    }

    /***
     * Check WiFi connection status
     * @param pvParameters
     */
    void vCheckWifi(void *pvParameters) {
        WifiConnector* wifi = (WifiConnector*)pvParameters;
        for (;;) {
            wifi->checkStatus();
            // Check every 1s
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer