#include "KeyboardInput.h"

#include <utility>

namespace TechnoKeyer {
    USB9350_KeyMouse* KeyboardInput::_usbKeyMouse = new USB9350_KeyMouse();

    /**
     * Initialize Keyboard Input
     */
    void KeyboardInput::begin() {
        static HardwareSerial SerialKey(2);
        SerialKey.begin(115200,
                        SERIAL_8N1,
                        KBD_RX_PIN,
                        KBD_TX_PIN);
        _usbKeyMouse->begin(SerialKey);
    }

    /**
     * Set onKeyInput Callback
     */
    void KeyboardInput::setOnKeyInput(onKeyInput callback) {
        _onKeyInput = std::move(callback);
    }

    /**
     * Check for key input
     */
    void KeyboardInput::checkKeyInput() {
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

            _onKeyInput(key);
        }
    }

    // Task to check key press from USB keyboard
    void vCheckKeyboardInput(void *pvParameters) {
        KeyboardInput *input;
        input = (KeyboardInput *)pvParameters;

        for ( ;; ) {
            input->checkKeyInput();
            // wait 2ms
            vTaskDelay(2 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer

