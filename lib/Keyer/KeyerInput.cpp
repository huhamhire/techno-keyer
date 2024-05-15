#include <KeyerInput.h>

HardwareSerial SerialKey(2);
USB9350_KeyMouse USBKeyMouse;

KeyerBuffer* _buffer;

uint8_t _lastKey = 0;
unsigned long _lastKeyTime = 0;

void initKeyerInput(KeyerBuffer* buffer) {
    SerialKey.begin(115200, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
    USBKeyMouse.begin(SerialKey);

    _buffer = buffer;
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
                _buffer->commitToSending();

                #if DEBUG_ALL
                Serial.printf("Sending Buffer: %s\n", _buffer->getSending());
                #endif                
            } else if (key == 0x08) {
                // Backspace
                _buffer->backspaceInput();

                #if DEBUG_ALL
                Serial.printf("Input Buffer: %s\n", _buffer->getInput());
                #endif
            } else if ((key >= 0x20) && (key <= 0x7e)) {
                // Characters
                keyasc = toupper((char)key);
                
                char *c = &keyasc;
                _buffer->appendInput(c);

                #if DEBUG_ALL
                Serial.printf("Input Buffer: %s\n", _buffer->getInput());
                #endif
            }
        }
        // wait 2ms
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
}
