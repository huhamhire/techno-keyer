#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include <Modes.h>
#include <Control/TunerControl.h>
#include <IO/AudioInput.h>
#include <Buffer/DisplayLineBuffer.h>
#include <Morse/MorseCodec.h>
#include <Morse/MorseDecoder.h>
#include <Morse/MorseBuzzer.h>


namespace TechnoKeyer {

    class Receiver: public ModeMutexComponent {
    public:
        void begin();
        void setTone(uint16_t tone);

        void onMorseEvent(uint8_t event);
        void onCharReceived(char c);
        void setOnCheckMode(onCheckMode callback);

        void activate() override;

        DisplayLineBuffer* getCharLine();
        DisplayLineBuffer* getMorseLine();

    private:
        void _initAudioInput();
        onCheckMode _onCheckMode = [](KeyerMode mode) {
            return true;
        };

        uint16_t _tone;

        static AudioInput *_audio;
        static MorseBuzzer *_buzzer;
        static TunerControl *_tuner;
        static MorseDecoder *_decoder;

        static DisplayLineBuffer *_charLine;
        static DisplayLineBuffer *_morseLine;
    };

} // TechnoKeyer

#endif // RECEIVER_H
