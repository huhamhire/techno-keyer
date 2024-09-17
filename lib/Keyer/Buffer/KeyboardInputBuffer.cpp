#include <Buffer/KeyboardInputBuffer.h>

namespace KeyboardKeyer {
    /**
     * Check if buffer is empty
     * @return
     */
    bool KeyboardInputBuffer::isEmpty() {
        return strlen(_buffer) == 0;
    }

    /**
     * Get buffer content
     * @return
     */
    char *KeyboardInputBuffer::getContent() {
        return _buffer;
    }

    /**
     * Get buffer size
     * @return
     */
    uint8_t KeyboardInputBuffer::getSize() {
        return strlen(_buffer);
    }

    /**
    * Append string to buffer
    * @param c
    */
    void KeyboardInputBuffer::append(char* c) {
        strcat(_buffer, c);
    }

    /**
     * Pop last character from buffer
     * @return
     */
    char KeyboardInputBuffer::pop() {
        char c = _buffer[strlen(_buffer) - 1];
        if (strlen(_buffer) > 0) {
            _buffer[strlen(_buffer) - 1] = '\0';
        }
        return c;
    }

    /**
    * Clear buffer
    */
    void KeyboardInputBuffer::clear() {
        memset(_buffer, 0, KBD_INPUT_BUFFER_SIZE);
    }
} // KeyboardKeyer