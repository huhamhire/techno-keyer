#ifndef KEYBOARD_INPUT_BUFFER_H
#define KEYBOARD_INPUT_BUFFER_H

#include <Arduino.h>

namespace TechnoKeyer {
    #define KBD_INPUT_BUFFER_SIZE 32

    class KeyboardInputBuffer {
    public:
        bool isEmpty();
        char *getContent();
        uint8_t getSize();
        void append(char* c);
        char pop();
        void clear();

    private:
        char _buffer[KBD_INPUT_BUFFER_SIZE] = "";
    };

} // TechnoKeyer

#endif // KEYBOARD_INPUT_BUFFER_H
