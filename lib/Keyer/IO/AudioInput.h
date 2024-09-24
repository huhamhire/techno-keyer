#ifndef AUDIO_INPUT_H
#define AUDIO_INPUT_H

#include <Arduino.h>
#include <Pinout.h>

namespace TechnoKeyer {
    class AudioInput {
    public:
        void begin();
        void checkSignal();

    private:
        uint8_t _lastState = 1;
    };

    [[noreturn]] void vCheckAuxSignal(void *pvParameters);
} // TechnoKeyer

#endif // AUDIO_INPUT_H
