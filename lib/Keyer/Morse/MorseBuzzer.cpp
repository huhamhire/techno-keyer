#include <Morse/MorseBuzzer.h>

namespace KeyboardKeyer {
    /**
     * Initialize Buzzer
     */
    void MorseBuzzer::init() {
        ledcSetup(BZ_CHANNEL, BZ_FREQ, BZ_RES);
        ledcAttachPin(BZ_PIN, BZ_CHANNEL);
        ledcWrite(BZ_CHANNEL, 0x00);
    }

    /**
     * Set Buzzer On
     */
    void MorseBuzzer::setOn() {
        ledcWrite(BZ_CHANNEL, 0x80);
    }

    /**
     * Set Buzzer Off
     */
    void MorseBuzzer::setOff() {
        ledcWrite(BZ_CHANNEL, 0x00);
    }
} // KeyboardKeyer
