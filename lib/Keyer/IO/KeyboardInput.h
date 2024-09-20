#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <Arduino.h>
#include <CH9350_USBKEY.h>

namespace KeyboardKeyer {
    #define KBD_RX_PIN 15
    #define KBD_TX_PIN 16

    class KeyboardInput {
    public:
        void begin();
        void checkKeyInput();
        void setOnKeyInput(std::function<void(uint8_t)> onKeyInput);

    private:
        static USB9350_KeyMouse *_usbKeyMouse;

        std::function<void(uint8_t)> _onKeyInput;
        uint8_t _lastKey = 0;
        unsigned long _lastKeyTime = 0;
    };

    void vCheckKeyboardInput(void *pvParameters);
} // KeyboardKeyer

#endif // KEYBOARD_INPUT_H
