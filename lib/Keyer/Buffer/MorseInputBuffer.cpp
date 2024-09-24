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
     * Get buffer size
     * @return
     */
    uint8_t MorseInputBuffer::size() {
        return _pos;
    }


    /**
     * Get coded morse from buffer
     * @return
     */
    uint8_t MorseInputBuffer::getCode() {
        return getCode(_pos);
    }

    /**
     * Get coded morse from buffer
     * @param len
     * @return
     */
    uint8_t MorseInputBuffer::getCode(uint8_t len) {
        if (_pos == 0) {
            return 0;
        }
        uint8_t code = 1;
        uint8_t pos = len < _pos ? len : _pos;
        for (uint8_t i = 0; i < pos; i++) {
            code = code << 1;
            code += _buffer[_pos - 1 - i];
        }
        return code;
    }

    /**
     * Shift buffer by size
     * @param size
     */
    void MorseInputBuffer::shift(uint8_t size) {
        if (size >= _pos) {
            clear();
            return;
        }
        for (uint8_t i = 0; i < _pos - size; i++) {
            _buffer[i] = _buffer[i + size];
        }
        _pos -= size;
        for (uint8_t i = _pos; i < MORSE_BUFFER_SIZE; i++) {
            _buffer[i] = 0;
        }
    }

    /**
     * Clear buffer
     */
    void MorseInputBuffer::clear() {
        memset(_buffer, 0, MORSE_BUFFER_SIZE * 2);
        _pos = 0;
    }


} // TechnoKeyer