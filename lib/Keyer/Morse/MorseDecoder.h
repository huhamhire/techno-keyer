#ifndef MORSE_DECODER_H
#define MORSE_DECODER_H

#include <Arduino.h>
#include <Buffer/MorseInputBuffer.h>
#include <Buffer/SignalEventsBuffer.h>
#include <Control/TunerControl.h>
#include <Morse/MorseCodec.h>

namespace TechnoKeyer {
    #define CHAR_BUFFER_SIZE    16
    #define MORSE_DEFAULT_WPM   20

    class MorseDecoder {
    public:
        void begin();
        void onSignalEvent(uint8_t event, uint16_t duration);
        char decodeChar();
        void setOnCharReceived(std::function<void(char)> callback);
        void setOnMorseEvent(std::function<void(uint8_t)> callback);
        void resetThreshold();

    private:
        void _updateThreshold();
        void _estimateWPM();

        std::function<void(char)> _onCharReceived = [](char){};
        std::function<void(uint8_t)> _onMorseEvent = [](uint8_t){};

        static MorseCodec *_codec;

        MorseInputBuffer *_morseBuffer;
        SignalEventsBuffer *_shortEvents;
        SignalEventsBuffer *_longEvents;

        char _charBuf[CHAR_BUFFER_SIZE] = "";

        uint8_t _wpm = MORSE_DEFAULT_WPM;
        uint16_t _thresholdMs;
        unsigned long _lastEventTime = 0;
    };

} // TechnoKeyer

#endif // MORSE_DECODER_H
