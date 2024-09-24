#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <Arduino.h>
#include <Pinout.h>
#include <CH9350_USBKEY.h>

namespace TechnoKeyer {

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
} // TechnoKeyer

#endif // KEYBOARD_INPUT_H
