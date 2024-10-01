#ifndef AUDIO_INPUT_H
#define AUDIO_INPUT_H

#include <Arduino.h>
#include <Pinout.h>

namespace TechnoKeyer {
    #define AUX_DEBOUNCE_MS     14
    #define AUX_MESSAGE_END_MS  600     // 1 WPM

    typedef std::function<void(uint8_t)> onSignal;
    typedef std::function<void(uint8_t, uint16_t)> onSignalEvent;
    typedef std::function<void()> onMsgEnd;

    class AudioInput {
    public:
        void begin();
        void checkSignal();
        void setOnSignal(onSignal callback);
        void setOnSignalEvent(onSignalEvent callback);
        void setOnMsgEnd(onMsgEnd callback);

    private:
        onSignal _onSignal = [](uint8_t){};
        onMsgEnd _onMsgEnd = []() {};
        onSignalEvent _onSignalEvent = [](uint8_t, uint16_t){};

        uint8_t _lastState = LOW;
        uint8_t _lastEvent = LOW;
        unsigned long _lastStateTime = 0;
    };

    [[noreturn]] void vCheckAuxSignal(void *pvParameters);
} // TechnoKeyer

#endif // AUDIO_INPUT_H
