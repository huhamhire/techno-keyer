#include "Receiver.h"

#include <utility>

namespace TechnoKeyer {
    AudioInput *Receiver::_audio = new AudioInput();
    MorseBuzzer *Receiver::_buzzer = new MorseBuzzer();
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

        // Default tone
        setTone(600);

        // Start audio input
        _initAudioInput();
    }

    /**
     * Set CW pitch tone
     * @param tone
     */
    void Receiver::setTone(uint16_t tone) {
        _tuner->setPitch(tone);
        _tone = tone;
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

        #if DEBUG_ALL
        Serial.printf("Morse line: [%.16s]\n", _morseLine->getContent());
        #endif
    }

    /**
     * Handle character received
     * @param c
     */
    void Receiver::onCharReceived(char c) {
        _charLine->append(c);

        #if DEBUG_ALL
        Serial.printf("Line buffer: [%.16s]\n", _charLine->getContent());
        #endif
    }

    /**
     * Set callback for check mode
     * @param callback
     */
    void Receiver::setOnCheckMode(onCheckMode callback) {
        _onCheckMode = std::move(callback);
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
     * Activate receiver
     */
    void Receiver::activate() {
        ModeMutexComponent::activate();
        _buzzer->setTone(_tone);
    }

    /**
     * Initialize audio input
     */
    void Receiver::_initAudioInput() {
        _audio->begin();
        _audio->setOnSignal([&](uint8_t signal) {
            if (signal == HIGH) {
                _buzzer->on();
            } else {
                _buzzer->off();
            }
        });
        _audio->setOnSignalEvent([&](uint8_t event, uint16_t duration) {
            if (!_onCheckMode(RX_MODE)) {
                // Skip if not in RX mode
                return;
            }
            keepBusy();
            _decoder->onSignalEvent(event, duration);
        });
        xTaskCreate(vCheckAuxSignal,
                    "vCheckAuxSignal",
                    2048,
                    _audio,
                    1,
                    nullptr);
    }
} // TechnoKeyer