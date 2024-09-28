#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include <Modes.h>
#include <Control/TunerControl.h>
#include <IO/AudioInput.h>
#include <Buffer/DisplayLineBuffer.h>
#include <Morse/MorseCodec.h>
#include <Morse/MorseDecoder.h>


namespace TechnoKeyer {

    class Receiver: public ModeMutexComponent {
    public:
        void begin();
        void setTone(uint16_t tone);

        void onMorseEvent(uint8_t event);
        void onCharReceived(char c);
        void setOnCheckMode(onCheckMode callback);

        DisplayLineBuffer* getCharLine();
        DisplayLineBuffer* getMorseLine();

    private:
        void _initAudioInput();
        onCheckMode _onCheckMode = [](KeyerMode mode) {
            return true;
        };

        static AudioInput *_audio;
        static TunerControl *_tuner;
        static MorseDecoder *_decoder;

        static DisplayLineBuffer *_charLine;
        static DisplayLineBuffer *_morseLine;
    };

} // TechnoKeyer

#endif // RECEIVER_H
