#include <KeyerInput.h>

// Input Constructor
KeyerInput::KeyerInput(KeyerBuffer* buffer) {
    _buffer = buffer;
}

// Initialize USB Keyboard Input
void KeyerInput::init() {
    static HardwareSerial SerialKey(2);
    static USB9350_KeyMouse USBKeyMouse;

    SerialKey.begin(115200, SERIAL_8N1, SERIAL_RX_PIN, SERIAL_TX_PIN);
    USBKeyMouse.begin(SerialKey);

    _usbKeyMouse = &USBKeyMouse;
}

// Get key press from USB keyboard
void KeyerInput::getKey() {
    uint8_t key;
    char keyasc='*';

    key = _usbKeyMouse->GetKey();
    if (key > 0) {
        // Debounce key press
        unsigned long now = millis();

        if (key == _lastKey && (now - _lastKeyTime) < DEBOUNCE_TIME) {
            return;
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
}

// Task to get key press from USB keyboard
void vGetKey(void *pvParameters) {
    KeyerInput *input;
    input = (KeyerInput *)pvParameters;

    for ( ;; ) {
        input->getKey();
        // wait 2ms
        vTaskDelay(2 / portTICK_PERIOD_MS);
    }
}
