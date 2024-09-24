#include "Receiver.h"

namespace TechnoKeyer {
    AudioInput *Receiver::_audio = new AudioInput();
    TunerControl *Receiver::_tuner = new TunerControl();
    MorseDecoder *Receiver::_decoder = new MorseDecoder();

    DisplayLineBuffer *Receiver::_charLine = new DisplayLineBuffer();
    DisplayLineBuffer *Receiver::_morseLine = new DisplayLineBuffer();

    /**
     * Initialize receiver
     */
    void Receiver::begin() {
        _tuner->begin();
        _decoder->begin();
        _decoder->setOnMorseEvent([&](uint8_t event) {
            onMorseEvent(event);
        });
        _decoder->setOnCharReceived([&](char c) {
            onCharReceived(c);
        });

        // Start audio input
        _initAudioInput();
    }

    /**
     * Handle morse event
     * @param event
     */
    void Receiver::onMorseEvent(uint8_t event) {
        switch (event) {
            case DIT:
                _morseLine->append('.');
                break;
            case DAH:
                _morseLine->append('-');
                break;
            case MORSE_SPACE:
                _morseLine->append(' ');
                break;
            default:
                break;
        }
    }

    /**
     * Handle character received
     * @param c
     */
    void Receiver::onCharReceived(char c) {
        _charLine->append(c);
    }

    /**
     * Get character line buffer
     * @return
     */
    DisplayLineBuffer *Receiver::getCharLine() {
        return _charLine;
    }

    /**
     * Get morse line buffer
     * @return
     */
    DisplayLineBuffer *Receiver::getMorseLine() {
        return _morseLine;
    }

    /**
     * Initialize audio input
     */
    void Receiver::_initAudioInput() {
        _audio->begin();
        _audio->setOnSignalEvent([&](uint8_t event, uint16_t duration) {
            _decoder->onSignalEvent(event, duration);
        });
        xTaskCreate(vCheckAuxSignal,
                    "vCheckAuxSignal",
                    2048,
                    _audio,
                    1,
                    NULL);
    }
} // TechnoKeyer