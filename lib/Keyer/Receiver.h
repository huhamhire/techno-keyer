#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include <Control/TunerControl.h>
#include <IO/AudioInput.h>
#include <Buffer/DisplayLineBuffer.h>
#include <Morse/MorseCodec.h>
#include <Morse/MorseDecoder.h>


namespace TechnoKeyer {

    class Receiver {
    public:
        void begin();
        void setTone(uint16_t tone);
        void onMorseEvent(uint8_t event);
        void onCharReceived(char c);
        DisplayLineBuffer* getCharLine();
        DisplayLineBuffer* getMorseLine();

    private:
        void _initAudioInput();

        static AudioInput *_audio;
        static TunerControl *_tuner;
        static MorseDecoder *_decoder;

        static DisplayLineBuffer *_charLine;
        static DisplayLineBuffer *_morseLine;
    };

} // TechnoKeyer

#endif // RECEIVER_H
