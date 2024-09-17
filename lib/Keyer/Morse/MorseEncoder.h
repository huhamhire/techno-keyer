#ifndef MORSE_ENCODER_H
#define MORSE_ENCODER_H

#include <Arduino.h>
#include <Buffer/MorseOutputBuffer.h>
#include <Morse/MorseBuzzer.h>

namespace KeyboardKeyer {

    #define CW_PIN 14

    struct t_mtab {
        char c, pat;
    };

    const struct t_mtab morsetab[] = {
            {'.', 106},
            {',', 115},
            {'?', 76},
            {'/', 41},
            {'A', 6},
            {'B', 17},
            {'C', 21},
            {'D', 9},
            {'E', 2},
            {'F', 20},
            {'G', 11},
            {'H', 16},
            {'I', 4},
            {'J', 30},
            {'K', 13},
            {'L', 18},
            {'M', 7},
            {'N', 5},
            {'O', 15},
            {'P', 22},
            {'Q', 27},
            {'R', 10},
            {'S', 8},
            {'T', 3},
            {'U', 12},
            {'V', 24},
            {'W', 14},
            {'X', 25},
            {'Y', 29},
            {'Z', 19},
            {'1', 62},
            {'2', 60},
            {'3', 56},
            {'4', 48},
            {'5', 32},
            {'6', 33},
            {'7', 35},
            {'8', 39},
            {'9', 47},
            {'0', 63}
    };

    #define N_MORSE (sizeof(morsetab)/sizeof(morsetab[0]))

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
        uint8_t _speed;

        MorseBuzzer *_buzzer = new MorseBuzzer();
        MorseOutputBuffer *_buffer;
    };

    void vSendMorse(void *pvParameters);

} // KeyboardKeyer

#endif // MORSE_ENCODER_H
