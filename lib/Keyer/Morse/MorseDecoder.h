#ifndef MORSE_DECODER_H
#define MORSE_DECODER_H

#include <Arduino.h>
#include <Buffer/MorseInputBuffer.h>
#include <Buffer/SignalEventsBuffer.h>
#include <Control/TunerControl.h>
#include <Morse/MorseCodec.h>

namespace TechnoKeyer {
    #define MORSE_DEFAULT_WPM   20

    typedef std::function<void(char)> onCharReceived;
    typedef std::function<void(uint8_t)> onMorseEvent;

    class MorseDecoder {
    public:
        void begin();
        void onSignalEvent(uint8_t event, uint16_t duration);
        char decodeChar();
        void setOnCharReceived(onCharReceived callback);
        void setOnMorseEvent(onMorseEvent callback);
        void clearEventsBuffer();
        void resetThreshold();

    private:
        void _updateThreshold();
        void _estimateWPM();

        onCharReceived _onCharReceived = [](char){};
        onMorseEvent _onMorseEvent = [](uint8_t){};

        static MorseCodec *_codec;

        MorseInputBuffer _morseBuffer;
        SignalEventsBuffer _shortEvents;
        SignalEventsBuffer _longEvents;

        uint8_t _wpm = MORSE_DEFAULT_WPM;
        uint16_t _thresholdMs;
        unsigned long _lastEventTime = 0;
    };

} // TechnoKeyer

#endif // MORSE_DECODER_H
