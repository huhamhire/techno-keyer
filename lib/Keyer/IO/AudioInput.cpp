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

            #if DEBUG_ALL
            Serial.print("State -> ");
            Serial.print(state);
            Serial.print(", Time: ");
            Serial.println(now);
            #endif

            uint16_t duration = now - _lastStateTime;
            if (duration > AUX_DEBOUNCE_MS) {
                _lastStateTime = now;
                _onSignalEvent(state, duration);
            }
        }
    }

    /**
     * Set callback on signal event
     */
    void AudioInput::setOnSignalEvent(std::function<void(uint8_t, uint16_t)> callback) {
        _onSignalEvent = callback;
    }

    /**
     * Task to check audio input signal
     * @param pvParameters
     */
    [[noreturn]] void vCheckAuxSignal(void *pvParameters) {
        auto *input = (AudioInput *)pvParameters;
        for ( ;; ) {
            input->checkSignal();
            vTaskDelay(5 / portTICK_PERIOD_MS);
        }
    }

} // TechnoKeyer