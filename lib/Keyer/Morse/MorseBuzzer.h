#ifndef MORSE_BUFFER_H
#define MORSE_BUFFER_H

#include <Arduino.h>

namespace KeyboardKeyer {

    #define BZ_PIN      2
    #define BZ_FREQ     750     // CW Pitch
    #define BZ_CHANNEL  0
    #define BZ_RES      8

    class MorseBuzzer {
    public:
        void init();
        void setOn();
        void setOff();
    };

} // KeyboardKeyer

#endif  // MORSE_BUFFER_H