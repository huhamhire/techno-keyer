#include "DisplayLineBuffer.h"

namespace TechnoKeyer {
    /**
     * Get buffer content
     * @return
     */
    char *DisplayLineBuffer::getContent() {
        return _buffer;
    }

    /**
     * Append a character to buffer
     * @param c
     */
    void DisplayLineBuffer::append(char c) {
        if (c == '\0') {
            return;
        }
        if (_pos >= DISPLAY_LINE_SIZE) {
            shift(1);
        }
        _buffer[_pos] = c;
        _pos++;
    }

    /**
     * Shift buffer by size
     * @param size
     */
    void DisplayLineBuffer::shift(uint8_t size) {
        if (size >= _pos) {
            clear();
            return;
        }
        for (uint8_t i = 0; i < DISPLAY_LINE_SIZE; i++) {
            uint8_t next = i + size;
            if (next < DISPLAY_LINE_SIZE) {
                _buffer[i] = _buffer[next];
            } else {
                _buffer[i] = 0;
            }
        }
        _pos -= size;
    }

    /**
     * Clear buffer
     */
    void DisplayLineBuffer::clear() {
        memset(_buffer, 0, DISPLAY_LINE_SIZE * 2);
        _pos = 0;
    }
} // TechnoKeyer