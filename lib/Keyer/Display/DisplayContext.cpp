#include <Display/DisplayContext.h>


namespace KeyboardKeyer {

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
     * @param value - Brightness value (0~1000)
     */
    void DisplayContext::setBrightness(uint16_t value) {
        if (value < 1000 && value > 0) {
            _bright = value;
        }
    }

    /**
     * Get display brightness.
     * @return
     */
    uint16_t DisplayContext::getBrightness() {
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
                return line < 1 ? _txBuf : _inputBuf;

            case 2:
                // RX Mode
                // Receiving messages from audio.
                return line < 1 ? _rxBuf : _decodeBuf;

            default:
                return (char *) "";
        }
    }
}
