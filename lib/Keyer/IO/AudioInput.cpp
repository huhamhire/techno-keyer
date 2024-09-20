#include "AudioInput.h"

namespace TechnoKeyer {
    /**
     * Initialize audio signal input
     */
    void AudioInput::begin() {
        pinMode(AUX_SIG_PIN, INPUT);
    }

    /**
     * Check signal input
     */
    void AudioInput::checkSignal() {
        uint8_t state = digitalRead(AUX_SIG_PIN);

        if (state != _lastState) {
            uint32_t now = millis();
            _lastState = state;
            Serial.print("State -> ");
            Serial.print(state);
            Serial.print(", Time: ");
            Serial.println(now);
        }
    }

    /**
     * Task to check audio input signal
     * @param pvParameters
     */
    void vCheckAuxSignal(void *pvParameters) {
        AudioInput *input = (AudioInput *)pvParameters;
        for ( ;; ) {
            input->checkSignal();
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
    }

} // TechnoKeyer