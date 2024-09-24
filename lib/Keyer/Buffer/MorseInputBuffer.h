#ifndef MORSE_INPUT_BUFFER_H
#define MORSE_INPUT_BUFFER_H

#include <Arduino.h>

namespace TechnoKeyer {
    #define MORSE_BUFFER_SIZE 32

    class MorseInputBuffer {
    public:
        MorseInputBuffer();
        void append(uint8_t signal);
        uint8_t size();
        uint8_t getCode();
        uint8_t getCode(uint8_t len);
        void shift(uint8_t size);
        void clear();

    private:
        uint8_t _buffer[MORSE_BUFFER_SIZE] = {};
        uint8_t _pos = 0;
    };

} // TechnoKeyer

#endif // MORSE_INPUT_BUFFER_H
