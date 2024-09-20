#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>
#include <Buffer/KeyboardInputBuffer.h>
#include <Buffer/MorseOutputBuffer.h>
#include <IO/KeyboardInput.h>
#include <Morse/MorseEncoder.h>


namespace KeyboardKeyer {
    class Transmitter {
    public:
        void begin();
        void onKeyInput(uint8_t key);

        KeyboardInputBuffer* getInputBuffer();
        MorseOutputBuffer* getOutputBuffer();

    private:
        void _handleBackspace();
        void _handleMessageCommit();

        static KeyboardInputBuffer *_inputBuffer;
        static MorseOutputBuffer *_outputBuffer;

        static KeyboardInput *_keyboard;
        static MorseEncoder *_morse;
    };

} // KeyboardKeyer

#endif // TRANSMITTER_H
