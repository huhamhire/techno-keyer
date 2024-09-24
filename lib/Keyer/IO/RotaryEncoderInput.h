#ifndef ROTARY_ENCODER_INPUT_H
#define ROTARY_ENCODER_INPUT_H

#include <Arduino.h>
#include <Pinout.h>
#include <AiEsp32RotaryEncoder.h>

namespace TechnoKeyer {
    #define ENCODER_STEPS 4

    class RotaryEncoderInput {
    public:
        void begin();
        void checkEncoder();
        void setValue(long value);
        void setBoundaries(long min, long max);

        void setOnValueChanged(std::function<void(long)> onValueChanged);
        void setOnButtonClicked(std::function<void()> onButtonClicked);

    private:
        static AiEsp32RotaryEncoder *_ec;

        std::function<void(long)> _onValueChanged = [](long value) {};
        std::function<void()> _onButtonClicked = []() {};
    };

    [[noreturn]] void vCheckRotaryEncoder(void *pvParameters);

} // TechnoKeyer

#endif // ROTARY_ENCODER_INPUT_H
