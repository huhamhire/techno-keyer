#include <Transmitter.h>

#include <utility>

namespace TechnoKeyer {
    KeyboardInputBuffer* Transmitter::_inputBuffer = new KeyboardInputBuffer();
    MorseOutputBuffer* Transmitter::_outputBuffer = new MorseOutputBuffer();

    KeyboardInput* Transmitter::_keyboard = new KeyboardInput();
    MorseEncoder* Transmitter::_morse = new MorseEncoder(_outputBuffer);

    /**
     * Start morse code transmitter
     */
    void Transmitter::begin() {
        // Initialize keyboard input
        _keyboard->begin();
        _keyboard->setOnKeyInput([&](uint8_t key) {
            if (!_onCheckMode(TX_MODE)) {
                // Skip if not in RX mode
                return;
            }
            onKeyInput(key);
        });

        // Buffer
         _outputBuffer->setPrefix((char*) "\x14");

        // Output
        _morse->setOnMorseSent([&]() {
            keepBusy();
        });
        xTaskCreate(vCheckKeyboardInput,
                    "vCheckKeyboardInput",
                    2048,
                    _keyboard,
                    1,
                    nullptr);

        // Initialize morse encoder
        _morse->setSpeed(20);
        xTaskCreate(vSendMorse,
                    "vSendMorse",
                    2048,
                    _morse,
                    1,
                    nullptr);
    }

    /**
     * Get input buffer
     * @return
     */
    KeyboardInputBuffer* Transmitter::getInputBuffer() {
        return _inputBuffer;
    }

    /**
     * Get output buffer
     * @return
     */
    MorseOutputBuffer* Transmitter::getOutputBuffer() {
        return _outputBuffer;
    }

    /**
     * Handle key input
     * @param key
     */
    void Transmitter::onKeyInput(uint8_t key) {
        static char keyChar = '*';
        switch (key) {
            case 0x08:
                // Backspace
                _handleBackspace();
                break;

            case 0x20:
            case 0x0d:
                // Space or Enter
                _handleMessageCommit();
                break;

            default:
                if ((key >= 0x20) && (key <= 0x7e)) {
                    // Characters
                    keyChar = toupper((char)key);
                    char* c = &keyChar;
                    _inputBuffer -> append(c);
                }
                break;
        }
    }

    /**
     * Set morse code speed in WPM
     * @param speed
     */
    void Transmitter::setSpeed(uint8_t speed) {
        _morse->setSpeed(speed);
    }

    /**
     * Set CW pitch tone
     * @param tone
     */
    void Transmitter::setTone(uint16_t tone) {
        _tone = tone;
        if (_active) {
            _morse->setTone(tone);
        }
    }

    /**
     * Activate transmitter
     */
    void Transmitter::activate() {
        ModeMutexComponent::activate();
        _morse->setTone(_tone);
    }

    /**
     * Deactivate transmitter
     */
    void Transmitter::deactivate() {
        ModeMutexComponent::deactivate();
        _inputBuffer->clear();
        _outputBuffer->clear();
    }

    /**
     * Set callback for check mode
     * @param callback
     */
    void Transmitter::setOnCheckMode(onCheckMode callback) {
        _onCheckMode = std::move(callback);
    }

    /**
     * Commit input buffer to output buffer
     */
    void Transmitter::_handleBackspace() {
        if (!_inputBuffer->isEmpty()) {
            _inputBuffer->pop();
        } else {
            char word[MORSE_OUT_BUFFER_SIZE] = "";
            char *pWord = word;
            pWord = _outputBuffer->popWord(pWord);
            if (pWord != nullptr) {
                _inputBuffer->append(word);
            }
        }
    }

    /**
     * Commit input buffer to output buffer
     */
    void Transmitter::_handleMessageCommit() {
        if (_inputBuffer->isEmpty()) {
            // Nothing to send
            return;
        } else if (_outputBuffer->getRemainingSpace() < _inputBuffer->getSize() + 1) {
            // Output buffer full
            return;
        }

        _outputBuffer->append(_inputBuffer->getContent());
        _outputBuffer->append((char*)" ");

        _inputBuffer->clear();

        #if DEBUG_ALL
        Serial.printf("Output line: [%.16s]\n", _outputBuffer->getContent());
        #endif
    }
} // TechnoKeyer