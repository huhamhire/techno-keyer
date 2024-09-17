#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>
#include <Buffer/KeyboardInputBuffer.h>
#include <Buffer/MorseOutputBuffer.h>
#include <Input/KeyboardInput.h>


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

        KeyboardInputBuffer *_inputBuffer;
        MorseOutputBuffer *_outputBuffer;

        KeyboardInput *_keyboard;
    };

} // KeyboardKeyer

#endif // TRANSMITTER_H
