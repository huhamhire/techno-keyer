#ifndef MORSE_OUTPUT_BUFFER_H
#define MORSE_OUTPUT_BUFFER_H

#include <Arduino.h>


namespace TechnoKeyer {
    #define MORSE_OUT_BUFFER_SIZE   128
    #define MORSE_OUT_PREFIX_LIMIT  3

    class MorseOutputBuffer {
    public:
        bool isEmpty();
        void setPrefix(char *prefix);
        char *getContent();
        char first();
        char shift();
        char *popWord();
        void append(char* c);
        void clear();
        uint8_t getRemainingSpace();

    private:
        char _buffer[MORSE_OUT_BUFFER_SIZE] = "";
        char *_prefix = nullptr;
        uint8_t _startIdx = 0;
    };

} // TechnoKeyer

#endif // MORSE_OUTPUT_BUFFER_H
