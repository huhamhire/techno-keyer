#ifndef ROTARY_ENCODER_INPUT_H
#define ROTARY_ENCODER_INPUT_H

#include <Arduino.h>
#include <Pinout.h>
#include <AiEsp32RotaryEncoder.h>

namespace TechnoKeyer {
    #define ENCODER_STEPS 4

    typedef std::function<void(long)> onValueChanged;
    typedef std::function<void()> onButtonClicked;

    class RotaryEncoderInput {
    public:
        void begin();
        void checkEncoder();
        void setValue(long value);
        void setBoundaries(long min, long max);
        static AiEsp32RotaryEncoder *getEncoder();

        void setOnValueChanged(onValueChanged callback);
        void setOnButtonClicked(onButtonClicked callback);
        void setOnButtonLongPressed(onButtonClicked callback);

    private:
        static AiEsp32RotaryEncoder *_ec;
        bool _isButtonDown = false;
        unsigned long _lastButtonDownTime = 0;

        onValueChanged _onValueChanged = [](long value) {};
        onButtonClicked _onButtonClicked = []() {};
        onButtonClicked _onButtonLongPressed = []() {};
    };

    [[noreturn]] void vCheckRotaryEncoder(void *pvParameters);

} // TechnoKeyer

#endif // ROTARY_ENCODER_INPUT_H
