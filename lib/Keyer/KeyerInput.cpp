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

// Handle key press
void KeyerInput::onKeyInput(uint8_t key) {
    static char keyasc = '*';
    if (key == 0x20 || key == 0x0d) {
        // Space or Enter
        _buffer->commitToSending();

        #if DEBUG_ALL
        Serial.printf("Sending Buffer: %s\n", _buffer->getSending());
        #endif                
    } else if (key == 0x08) {
        // Backspace
        if (!_buffer->isInputEmpty()) {
            _buffer->backspaceInput();
        } else {
            _buffer->revertCommitted();
        }

        #if DEBUG_ALL
        Serial.printf("Input Buffer: %s\n", _buffer->getInput());
        #endif
    } else if ((key >= 0x20) && (key <= 0x7e)) {
        // Characters
        keyasc = toupper((char)key);
        char* c = &keyasc;
        _buffer->appendInput(c);

        #if DEBUG_ALL
        Serial.printf("Input Buffer: %s\n", _buffer->getInput());
        #endif
    }
}

// Get key press from USB keyboard
void KeyerInput::getKey() {
    uint8_t key;
    key = _usbKeyMouse->GetKey();
    if (key > 0) {
        // Debounce key press
        unsigned long now = millis();

        uint8_t debounce_time = 140;
        if (key == 0x08) {
            // backspace
            debounce_time = 80;
        }
        if (key == _lastKey && (now - _lastKeyTime) < debounce_time) {
            return;
        } else {
            _lastKey = key;
            _lastKeyTime = now;
        }

        onKeyInput(key);
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
