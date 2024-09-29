#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>
#include <Modes.h>
#include <Buffer/KeyboardInputBuffer.h>
#include <Buffer/MorseOutputBuffer.h>
#include <IO/KeyboardInput.h>
#include <Morse/MorseEncoder.h>


namespace TechnoKeyer {
    class Transmitter: public ModeMutexComponent {
    public:
        void begin();
        void onKeyInput(uint8_t key);
        void setSpeed(uint8_t speed);
        void setTone(uint16_t tone);
        void setOnCheckMode(onCheckMode callback);

        void activate() override;
        void deactivate() override;

        KeyboardInputBuffer* getInputBuffer();
        MorseOutputBuffer* getOutputBuffer();

    private:
        void _handleBackspace();
        void _handleMessageCommit();

        uint16_t _tone = 600;

        onCheckMode _onCheckMode = [](KeyerMode mode) {
            return true;
        };

        static KeyboardInputBuffer *_inputBuffer;
        static MorseOutputBuffer *_outputBuffer;

        static KeyboardInput *_keyboard;
        static MorseEncoder *_morse;
    };

} // TechnoKeyer

#endif // TRANSMITTER_H
