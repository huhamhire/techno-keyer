#ifndef MORSE_OUTPUT_BUFFER_H
#define MORSE_OUTPUT_BUFFER_H

#include <Arduino.h>

namespace TechnoKeyer {

    #define MORSE_OUT_BUFFER_SIZE 128

    class MorseOutputBuffer {
    public:
        bool isEmpty();
        char *getContent();
        char shift();
        char *popWord();
        void append(char* c);
        void clear();
        uint8_t getRemainingSpace();

    private:
        char _buffer[MORSE_OUT_BUFFER_SIZE] = "";
    };

} // TechnoKeyer

#endif // MORSE_OUTPUT_BUFFER_H
