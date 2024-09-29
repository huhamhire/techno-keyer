#ifndef MORSE_BUFFER_H
#define MORSE_BUFFER_H

#include <Arduino.h>
#include <Pinout.h>

namespace TechnoKeyer {

    #define BZ_FREQ     750     // CW Pitch
    #define BZ_CHANNEL  0
    #define BZ_RES      8

    class MorseBuzzer {
    public:
        void init();
        void setTone(uint16_t tone);
        void on();
        void off();
    };

} // TechnoKeyer

#endif  // MORSE_BUFFER_H
