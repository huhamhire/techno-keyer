#include <Display/DisplayContext.h>


namespace TechnoKeyer {
    /**
     * Get display mode.
     * @return
     */
    uint8_t DisplayContext::getMode() {
        return _mode;
    }

    /**
     * Set display mode.
     * @param mode - Display mode, 0 - config, 1 - tx, 2 - rx
     */
    void DisplayContext::setMode(uint8_t mode) {
        if (mode < DISPLAY_MODES) {
            _mode = mode;
        }
    }

    /**
     * Set display brightness.
     * @param value - Brightness value (0~100)
     */
    void DisplayContext::setBrightness(uint16_t value) {
        if (value < 100 && value > 0) {
            _bright = value;
        }
    }

    /**
     * Get display brightness.
     * @return
     */
    uint16_t DisplayContext::getBrightness() const
    {
        return _bright;
    }

    /**
     * Set title line.
     * @param title - Title line
     */
    void DisplayContext::setTitleLine(char *title) {
        _titleBuf = title;
    }

    /**
     * Set value line.
     * @param value - Value line
     */
    void DisplayContext::setValueLine(char *value) {
        _valueBuf = value;
    }

    /**
     * Set transmit lines.
     * @param tx - Transmit line
     * @param input - Input line
     */
    void DisplayContext::setTransmitLines(char *tx, char *input) {
        _txBuf = tx;
        _inputBuf = input;
    }

    /**
     * Set receive lines.
     * @param rx - Receive line
     * @param decode - Decode line
     */
    void DisplayContext::setReceiveLines(char *rx, char *decode) {
        _rxBuf = rx;
        _decodeBuf = decode;
    }

    /**
     * Get line buffer for current display mode.
     * @param line - Line number
     * @return Line characters buffer
     */
    char *DisplayContext::getDisplayLine(uint8_t line) {
        if (line > DISPLAY_LINES) {
            return (char *) "";
        }
        switch (_mode) {
            case 0:
                // Custom Mode
                // Custom title + value line
                return line < 1 ? _titleBuf : _valueBuf;

            case 1:
                // TX Mode
                // Transmitting morse codes from keyboard.
                return line < 1 ? _txBuf : _getInputLine();

            case 2:
                // RX Mode
                // Receiving messages from audio.
                return line < 1 ? _decodeBuf : _rxBuf;

            default:
                return (char *) "";
        }
    }

    /**
     * Get input line with cursor.
     * @return
     */
    char *DisplayContext::_getInputLine() {
        size_t len = strlen(_inputBuf);
        unsigned long now = millis();
        // Prompt & cursor
        _inputLine[0] = '\x1D';
        char cursor = now / 400 % 2 == 0 ? '\x5F' : ' ';

        if (len > DISPLAY_LINE_SIZE - 2) {
            strcpy(_inputLine + 1, _inputBuf + len + 2 - DISPLAY_LINE_SIZE);
            strcat(_inputLine, &cursor);
        } else {
            strcpy(_inputLine + 1, _inputBuf);
            _inputLine[len + 1] = cursor;
            _inputLine[len + 2] = '\0';
        }
        return _inputLine;
    }
}
