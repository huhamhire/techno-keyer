#include "MorseDecoder.h"

#include <utility>

namespace TechnoKeyer {
    MorseCodec *MorseDecoder::_codec = new MorseCodec();

    /**
     * Initialize morse decoder
     */
    void MorseDecoder::begin() {
        resetThreshold();
    }


    /**
     * Handle signal event
     * @param event
     * @param duration
     */
    void MorseDecoder::onSignalEvent(uint8_t event, uint16_t duration) {
        _lastEventTime = millis();
        uint16_t shortAvg = _shortEvents.getAverageTime();
        char ch;
        if (event == LOW) {
            // LOW signal
            if (duration > _thresholdMs * 2) {
                // End of word (7 units)
                ch = decodeChar();
                _onCharReceived(ch);
                _onCharReceived(' ');
                _onMorseEvent(MORSE_SPACE);
            } else if (duration > _thresholdMs && duration > shortAvg * 2) {
                // End of character (3 units)
                // Char end
                ch = decodeChar();
                _longEvents.appendEventTime(duration);
                _onCharReceived(ch);
                _onMorseEvent(MORSE_SPACE);
            } else {
                // space (1 unit)
                _shortEvents.appendEventTime(duration);
            }
        } else {
            // HIGH signal
            if (duration > _thresholdMs && duration > shortAvg * 2) {
                // Dash (3 units)
                _morseBuffer.append(DAH);
                _longEvents.appendEventTime(duration);
                _onMorseEvent(DAH);
            } else {
                // Dot (1 uint)
                _morseBuffer.append(DIT);
                _shortEvents.appendEventTime(duration);
                _onMorseEvent(DIT);
            }
            if (_morseBuffer.size() >= MORSE_LEN_MAX) {
                // Force decode
                ch = decodeChar();
                if (ch != '\0') {
                    _onCharReceived(ch);
                }
            }
        }
        _updateThreshold();
        _estimateWPM();
    }

    /**
     * Update threshold duration
     */
    void MorseDecoder::_updateThreshold() {
        uint16_t shortAvg = _shortEvents.getAverageTime();
        uint16_t longAvg = _longEvents.getAverageTime();
        if (shortAvg == 0 && longAvg == 0) {
            return;
        } else {
            if (shortAvg == 0) {
                shortAvg = longAvg / 3;
            } else if (longAvg == 0) {
                longAvg = shortAvg * 3;
            }
        }
        // New threshold by geometric mean
        // http://www.k4icy.com/cw_decoder.html
        _thresholdMs = (uint16_t)sqrt(shortAvg * longAvg);
    }

    /**
     * Estimate WPM by threshold duration
     */
    void MorseDecoder::_estimateWPM() {
        _wpm = ((uint16_t) 1200 / _thresholdMs / 2);
    }

    /**
     * Decode character from morse buffer
     * @return
     */
    char MorseDecoder::decodeChar() {
        uint8_t size = _morseBuffer.size();
        if (size == 0) {
            return '\0';
        } else {
            uint8_t len = size < MORSE_LEN_MAX ? size : MORSE_LEN_MAX;
            // Try to decode from max length
            for (uint8_t i = len; i > 0; i--) {
                uint8_t code = _morseBuffer.getCode(i);
                char ch = _codec->getChar(code);
                if (ch != '~') {
                    // Shift buffer
                    _morseBuffer.shift(i);
                    return ch;
                }
            }
            // Should not reach here
            return '~';
        }
    }

    /**
     * Set callback on char received
     * @param callback
     */
    void MorseDecoder::setOnCharReceived(onCharReceived callback) {
        _onCharReceived = std::move(callback);
    }

    /**
     * Set callback on morse event
     * @param callback
     */
    void MorseDecoder::setOnMorseEvent(onMorseEvent callback) {
        _onMorseEvent = std::move(callback);
    }

    /**
     * Clear events buffer
     */
    void MorseDecoder::clearEventsBuffer() {
        _morseBuffer.clear();
        _shortEvents.clear();
        _longEvents.clear();
    }

    /**
     * Reset threshold duration to default
     */
    void MorseDecoder::resetThreshold() {
        _thresholdMs = 1200 / MORSE_DEFAULT_WPM * 2; // default by wpm
    }
} // TechnoKeyer