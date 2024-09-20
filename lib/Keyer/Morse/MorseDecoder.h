#ifndef MORSE_DECODER_H
#define MORSE_DECODER_H

#include <Arduino.h>
#include <Control/TunerControl.h>
#include <IO/AudioInput.h>

namespace KeyboardKeyer {

    class MorseDecoder {
    public:
        void begin();

    private:
        void _initAudioInput();

        static TunerControl *_tuner;
        static AudioInput *_audio;
    };

} // KeyboardKeyer

#endif // MORSE_DECODER_H
