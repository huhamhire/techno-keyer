#include "MorseDecoder.h"

namespace KeyboardKeyer {
    TunerControl *MorseDecoder::_tuner = new TunerControl();
    AudioInput *MorseDecoder::_audio = new AudioInput();

    /**
     * Initialize morse decoder
     */
    void MorseDecoder::begin() {
        _tuner->begin();
        _initAudioInput();
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

} // KeyboardKeyer