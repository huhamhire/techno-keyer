#include "Receiver.h"

namespace TechnoKeyer {
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
} // TechnoKeyer