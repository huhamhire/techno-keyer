#include "MorseDecoder.h"

namespace TechnoKeyer {
    MorseCodec *MorseDecoder::_codec = new MorseCodec();
    AudioInput *MorseDecoder::_audio = new AudioInput();

    /**
     * Initialize morse decoder
     */
    void MorseDecoder::begin() {
        _morseBuffer = new MorseInputBuffer();
        _shortEvents = new SignalEventsBuffer();
        _longEvents = new SignalEventsBuffer();
        resetThreshold();

        _initAudioInput();
    }


    /**
     * Handle signal event
     * @param event
     * @param duration
     */
    void MorseDecoder::onSignalEvent(uint8_t event, uint16_t duration) {
        _lastEventTime = millis();
        char ch;
        if (event == LOW) {
            // LOW signal
            if (duration > _thresholdMs * 2) {
                // End of word (7 units)
                ch = decodeChar();
                // todo on word end
            } else if (duration > _thresholdMs) {
                // End of character (3 units)
                ch = decodeChar();
                _longEvents->appendEventTime(duration);
            } else {
                // space (1 unit)
                _shortEvents->appendEventTime(duration);
            }
        } else {
            // HIGH signal
            if (duration > _thresholdMs) {
                // Dash (3 units)
                _morseBuffer->append(DAH);
                _longEvents->appendEventTime(duration);
            } else {
                // Dot (1 uint)
                _morseBuffer->append(DIT);
                _shortEvents->appendEventTime(duration);
            }
            if (_morseBuffer->size() >= MORSE_LEN_MAX) {
                // Force decode
                ch = decodeChar();
            }
        }
        _updateThreshold();
        _estimateWPM();
    }

    /**
     * Update threshold duration
     */
    void MorseDecoder::_updateThreshold() {
        uint16_t shortAvg = _shortEvents->getAverageTime();
        uint16_t longAvg = _longEvents->getAverageTime();
        if (shortAvg == 0 || longAvg == 0) {
            return;
        }
        // New threshold by geometric mean
        // http://www.k4icy.com/cw_decoder.html
        _thresholdMs = (uint16_t)sqrt(shortAvg * longAvg);
    }

    /**
     * Estimate WPM by threshold duration
     */
    void MorseDecoder::_estimateWPM() {
        _wpm = (uint8_t) (1200 / _thresholdMs / 2);
    }

    /**
     * Decode character from morse buffer
     * @return
     */
    char MorseDecoder::decodeChar() {
        uint8_t size = _morseBuffer->size();
        if (size == 0) {
            return '\0';
        } else {
            uint8_t len = size < MORSE_LEN_MAX ? size : MORSE_LEN_MAX;
            // Try to decode from max length
            for (uint8_t i = len; i > 0; i--) {
                uint8_t code = _morseBuffer->getCode(i);
                char ch = _codec->getChar(code);
                if (ch != '~') {
                    // Shift buffer
                    _morseBuffer->shift(i);
                    return ch;
                }
            }
            // Should not reach here
            return '~';
        }
    }

    /**
     * Reset threshold duration to default
     */
    void MorseDecoder::resetThreshold() {
        _thresholdMs = 1200 / MORSE_DEFAULT_WPM * 2; // default by wpm
    }

    /**
     * Initialize audio input
     */
    void MorseDecoder::_initAudioInput() {
        _audio->begin();
        xTaskCreate(vCheckAuxSignal,
                    "vCheckAuxSignal",
                    2048,
                    _audio,
                    1,
                    NULL);
    }

} // TechnoKeyer