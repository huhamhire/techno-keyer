#ifndef DISPLAY_LINE_BUFFER_H
#define DISPLAY_LINE_BUFFER_H

#include <Arduino.h>

namespace TechnoKeyer {
    #define DISPLAY_LINE_SIZE 16

    class DisplayLineBuffer {
    public:
        char *getContent();
        void append(char c);
        void shift(uint8_t size);
        void clear();

    private:
        char _buffer[DISPLAY_LINE_SIZE] = "";
        uint8_t _pos = 0;
    };
} // TechnoKeyer

#endif // DISPLAY_LINE_BUFFER_H
