#include "MorseInputBuffer.h"

namespace TechnoKeyer {
    MorseInputBuffer::MorseInputBuffer() {
        clear();
    }

    /**
     * Append morse signal to buffer
     * @param signal
     */
    void MorseInputBuffer::append(uint8_t signal) {
        if (_pos >= MORSE_BUFFER_SIZE) {
            // Overflow
            return;
        }
        _buffer[_pos] = signal;
        _pos++;
    }

    /**
     * Clear buffer
     */
    void MorseInputBuffer::clear() {
        memset(_buffer, 0, MORSE_BUFFER_SIZE * 2);
        _pos = 0;
    }
} // TechnoKeyer