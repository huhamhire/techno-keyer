#ifndef AUDIO_INPUT_H
#define AUDIO_INPUT_H

#include <Arduino.h>
#include <Pinout.h>

namespace TechnoKeyer {
    #define AUX_DEBOUNCE_MS   15

    typedef std::function<void(uint8_t, uint16_t)> onSignalEvent;

    class AudioInput {
    public:
        void begin();
        void checkSignal();
        void setOnSignalEvent(onSignalEvent callback);

    private:
        onSignalEvent _onSignalEvent = [](uint8_t, uint16_t){};

        uint8_t _lastState = HIGH;
        unsigned long _lastStateTime = 0;
    };

    [[noreturn]] void vCheckAuxSignal(void *pvParameters);
} // TechnoKeyer

#endif // AUDIO_INPUT_H
