#include <Buffer/MorseOutputBuffer.h>

namespace KeyboardKeyer {
    /**
    * Check if buffer is empty
    * @return
    */
    bool MorseOutputBuffer::isEmpty() {
        return strlen(_buffer) == 0;
    }

    /**
     * Get buffer content
     */
    char *MorseOutputBuffer::getContent() {
        return _buffer;
    }

    /**
    * Shift output buffer
    * @return
    */
    char MorseOutputBuffer::shift() {
        char c = _buffer[0];

        uint8_t len = strlen(_buffer);
        for (int i = 0; i < len - 1; i++) {
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
        strcat(_buffer, c);
    }

    /**
     * Pop word from buffer
     * @return
     */
    char *MorseOutputBuffer::popWord() {
        uint8_t len = strlen(_buffer);
        if (len == 0) {
            return "";
        }
        // Find last space
        uint8_t i = len - 2;
        while (i >= 0 && _buffer[i] != ' ') {
            i--;
        }
        uint8_t word_start = i + 1;

        char *word = "";

        // Copy back to input buffer
        if (i > 0) {
            strncpy(word, _buffer + word_start, len - word_start - 1);
        }
        // Remove last word
        _buffer[word_start] = '\0';

        return word;
    }

    /**
     * Get remaining space in buffer
     * @return
     */
    uint8_t MorseOutputBuffer::getRemainingSpace() {
        return MORSE_OUT_BUFFER_SIZE - strlen(_buffer);
    }

    /**
    * Clear buffer
    */
    void MorseOutputBuffer::clear() {
        memset(_buffer, 0, MORSE_OUT_BUFFER_SIZE);
    }
} // KeyboardKeyer