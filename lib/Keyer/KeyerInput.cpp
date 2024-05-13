#include <KeyerInput.h>

HardwareSerial SerialKey(2);
USB9350_KeyMouse USBKeyMouse;

char* _input;

char _lastKey = '*';
unsigned long _lastKeyTime = 0;

void KeyerInputInit(char* input) {
    SerialKey.begin(115200, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
    USBKeyMouse.begin(SerialKey);

    _input = input;
}

// Task to get key press from USB keyboard
void vGetKey(void *pvParameters) {
    for ( ;; ) {
        int key;
        char keyasc='*';

        key = USBKeyMouse.GetKey();
        if (key > 0) {
            if ((key >= 0x20) && (key <= 0x7e)) {
                keyasc = toupper((char)key);
                unsigned long now = millis();

                // Debounce key press
                if (keyasc == _lastKey && now - _lastKeyTime < DEBOUNCE_TIME) {
                    continue;
                } else {
                    _lastKey = keyasc;
                    _lastKeyTime = now;
                }
                
                char *c = &keyasc;
                strlcat(_input, c, INPUT_BUFFER_SIZE);

                #if DEBUG_ALL
                Serial.printf("Buffer: %s\n", _input);
                #endif
            }
        }
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
}
