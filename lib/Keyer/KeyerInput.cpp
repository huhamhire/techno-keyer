#include <KeyerInput.h>

HardwareSerial SerialKey(2);
USB9350_KeyMouse USBKeyMouse;

char* _input;
char* _sending;

uint8_t _lastKey = 0;
unsigned long _lastKeyTime = 0;

void initKeyerInput(char* input, char* sending) {
    SerialKey.begin(115200, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
    USBKeyMouse.begin(SerialKey);

    _input = input;
    _sending = sending;
}

// Task to get key press from USB keyboard
void vGetKey(void *pvParameters) {
    for ( ;; ) {
        uint8_t key;
        char keyasc='*';

        key = USBKeyMouse.GetKey();
        if (key > 0) {
            // Debounce key press
            unsigned long now = millis();

            if (key == _lastKey && (now - _lastKeyTime) < DEBOUNCE_TIME) {
                continue;
            } else {
                _lastKey = key;
                _lastKeyTime = now;
            }

            if (key == 0x20 || key == 0x0d) {
                // Space or Enter
                strcat(_sending, _input);
                strcat(_sending, " ");
                
                // clear input buffer
                _input[0] = '\0';

                #if DEBUG_ALL
                Serial.printf("Sending Buffer: %s\n", _sending);
                #endif                
            } else if (key == 0x08) {
                // Backspace
                if (strlen(_input) > 0) {
                    _input[strlen(_input) - 1] = '\0';
                }

                #if DEBUG_ALL
                Serial.printf("Input Buffer: %s\n", _input);
                #endif
            } else if ((key >= 0x20) && (key <= 0x7e)) {
                // Characters
                keyasc = toupper((char)key);
                
                char *c = &keyasc;
                strcat(_input, c);

                #if DEBUG_ALL
                Serial.printf("Input Buffer: %s\n", _input);
                #endif
            }
        }
        // wait 2ms
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
}
