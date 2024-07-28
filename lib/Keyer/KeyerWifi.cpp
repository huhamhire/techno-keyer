#include <KeyerWifi.h>


KeyerWifi::KeyerWifi() {
    ssid = STA_SSID;
    password = STA_PSK;

    prev_ms = 0;
    prev_connect_ms = 0;
    connected = false;
}

// 建立连接
void KeyerWifi::connect() {
    prev_connect_ms = millis();
    Serial.println("WIFI connecting to: " + String(ssid));

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

// 检查连接状态
void KeyerWifi::check() {
    unsigned long now = millis();
    if (now - prev_ms < WIFI_CHECK_INTERVAL) {
        return;
    }
    prev_ms = now;

    if (WiFi.status() == WL_CONNECTED && !connected) {
         // 新建立连接
        connected = true;
        String ip = WiFi.localIP().toString();

        char msg[100];
        sprintf(msg, "WIFI connected: %s, IP: %s", ssid, ip.c_str());
        Serial.println(msg);
    } else if (WiFi.status() != WL_CONNECTED && connected) {
        // 连接断开
        connected = false;
        Serial.println("WIFI disconnected");
    }

    // 重连检查
    if (now - prev_connect_ms < WIFI_RECO_INTERVAL) {
        return;
    }
    // 重连
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.disconnect();
        connect();
    }
}

// 获取单例
KeyerWifi* KeyerWifi::instance = 0;
KeyerWifi* KeyerWifi::getInstance() {
    if (instance == 0) {
        instance = new KeyerWifi();
    }
    return instance;
}

KeyerWifi wifiClient = *(KeyerWifi::getInstance());
