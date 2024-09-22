#ifndef MORSE_ENCODER_H
#define MORSE_ENCODER_H

#include <Arduino.h>
#include <Buffer/MorseOutputBuffer.h>
#include <Morse/MorseCodec.h>
#include <Morse/MorseBuzzer.h>

namespace TechnoKeyer {
    #define CW_PIN 14

    class MorseEncoder {
    public:
        explicit MorseEncoder(MorseOutputBuffer *buffer);

        void setSpeed(uint8_t speed);
        void sendChar(char c);
        void sendBuffer();

    private:
        void _updateSpeed(uint8_t);
        void _sendDit();
        void _sendDah();

        uint16_t _dotTimeMs;
        uint16_t _dashTimeMs;
        uint8_t _speed = 20;

        static MorseCodec *_codec;
        static MorseBuzzer *_buzzer;
        MorseOutputBuffer *_buffer;
    };

    void vSendMorse(void *pvParameters);
} // TechnoKeyer

#endif // MORSE_ENCODER_H
