#include <Transmitter.h>

namespace KeyboardKeyer {
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
            onKeyInput(key);
        });
        xTaskCreate(vCheckKeyboardInput,
                    "vCheckKeyboardInput",
                    2048,
                    _keyboard,
                    1,
                    NULL);

        // Initialize morse encoder
        _morse->setSpeed(20);
        xTaskCreate(vSendMorse,
                    "vSendMorse",
                    2048,
                    _morse,
                    1,
                    NULL);
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
     * Commit input buffer to output buffer
     */
    void Transmitter::_handleBackspace() {
        if (!_inputBuffer->isEmpty()) {
            _inputBuffer->pop();
        } else {
            char* word = _outputBuffer->popWord();
            _inputBuffer->append(word);
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
        _outputBuffer->append(" ");

        _inputBuffer->clear();
    }

} // KeyboardKeyer