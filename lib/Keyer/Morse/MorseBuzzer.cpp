#include <Morse/MorseBuzzer.h>

namespace TechnoKeyer {
    /**
     * Initialize Buzzer
     */
    void MorseBuzzer::init() {
        ledcSetup(BZ_CHANNEL, BZ_FREQ, BZ_RES);
        ledcAttachPin(BZ_PIN, BZ_CHANNEL);
        ledcWrite(BZ_CHANNEL, 0x00);
    }

    /**
     * Set Buzzer Tone
     */
    void MorseBuzzer::setTone(uint16_t tone) {
        ledcChangeFrequency(BZ_CHANNEL, tone, BZ_RES);
    }

    /**
     * Set Buzzer On
     */
    void MorseBuzzer::on() {
        ledcWrite(BZ_CHANNEL, 0x80);
    }

    /**
     * Set Buzzer Off
     */
    void MorseBuzzer::off() {
        ledcWrite(BZ_CHANNEL, 0x00);
    }
} // TechnoKeyer
