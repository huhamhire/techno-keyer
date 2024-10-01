#include <Buffer/MorseOutputBuffer.h>

namespace TechnoKeyer {
    /**
    * Check if buffer is empty
    * @return
    */
    bool MorseOutputBuffer::isEmpty() {
        return strlen(_buffer) - _startIdx == 0;
    }

    /**
     * Set prefix
     * @param prefix
     */
    void MorseOutputBuffer::setPrefix(char *prefix) {
        size_t len = strlen(prefix);
        if (len > MORSE_OUT_PREFIX_LIMIT) {
            return;
        }
        _prefix = prefix;

        strncpy(_buffer, prefix, len);
        _startIdx = len;
    }

    /**
     * Get buffer content
     */
    char *MorseOutputBuffer::getContent() {
        return _buffer;
    }

    /**
     * Get first character in buffer
     * @return
     */
    char MorseOutputBuffer::first() {
        return _buffer[_startIdx];
    }

    /**
    * Shift output buffer
    * @return
    */
    char MorseOutputBuffer::shift() {
        char c = _buffer[_startIdx];

        uint8_t len = strlen(_buffer);
        for (int i = _startIdx; i < len - 1; i++) {
            _buffer[i] = _buffer[i + 1];
        }
        _buffer[len - 1] = '\0';

        return c;
    }

    /**
    * Append string to buffer
    * @param c
    */
    void MorseOutputBuffer::append(char* c) {
        uint8_t len = strlen(c);
        uint8_t remaining = getRemainingSpace();
        if (len > remaining) {
            return;
        }
        strcat(_buffer, c);
    }

    /**
     * Pop word from buffer
     * @return
     */
    char *MorseOutputBuffer::popWord(char* word) {
        uint8_t len = strlen(_buffer);
        if (len == _startIdx) {
            return nullptr;
        }
        // Find last space
        uint8_t i = len - 2;
        while (i >= _startIdx && _buffer[i] != ' ') {
            i--;
        }
        uint8_t word_start = i + 1;

        // Copy back to input buffer
        uint16_t size = len - word_start - 1;
        if (word_start > _startIdx) {
            strncpy(word, _buffer + word_start, size);

            // Remove last word
            _buffer[word_start] = '\0';
            return word;
        }
        return nullptr;
    }

    /**
     * Get remaining space in buffer
     * @return
     */
    uint8_t MorseOutputBuffer::getRemainingSpace() {
        return MORSE_OUT_BUFFER_SIZE - strlen(_buffer) - _startIdx;
    }

    /**
    * Clear buffer
    */
    void MorseOutputBuffer::clear() {
        memset(_buffer, 0, MORSE_OUT_BUFFER_SIZE);
        _startIdx = 0;
        if (_prefix != nullptr) {
            setPrefix(_prefix);
        }
    }
} // TechnoKeyer