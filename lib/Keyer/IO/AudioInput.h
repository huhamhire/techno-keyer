#ifndef AUDIO_INPUT_H
#define AUDIO_INPUT_H

#include <Arduino.h>

namespace TechnoKeyer {

    #define AUX_SIG_PIN   8

    class AudioInput {
    public:
        void begin();
        void checkSignal();

    private:
        uint8_t _lastState = 1;
    };

    void vCheckAuxSignal(void *pvParameters);
} // TechnoKeyer

#endif // AUDIO_INPUT_H
