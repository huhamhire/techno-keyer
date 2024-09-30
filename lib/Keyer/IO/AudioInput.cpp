#include "AudioInput.h"

#include <utility>

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
        uint8_t state = digitalRead(AUX_SIG_PIN) ? LOW : HIGH;

        uint32_t now = millis();
        uint16_t duration = now - _lastStateTime;

        if (
                state != _lastState ||
                // Append last event
                (state != _lastEvent && duration > 1000))
        {
            if (duration > AUX_DEBOUNCE_MS) {
                #if DEBUG_ALL
                Serial.print("AUX: ");
                Serial.print(state);
                Serial.print(", Duration: ");
                Serial.println(duration);
                #endif

                // Signal changed
                _onSignal(state);
                _onSignalEvent(_lastState, duration);
                _lastEvent = _lastState;

                _lastState = state;
                _lastStateTime = now;
            }
        }
    }

    /**
     * Set callback on audio signal change
     * @param callback
     */
    void AudioInput::setOnSignal(onSignal callback) {
        _onSignal = std::move(callback);
    }

    /**
     * Set callback on signal event
     */
    void AudioInput::setOnSignalEvent(onSignalEvent callback) {
        _onSignalEvent = std::move(callback);
    }


    /**
     * Task to check audio input signal
     * @param pvParameters
     */
    void vCheckAuxSignal(void *pvParameters) {
        auto *input = (AudioInput *)pvParameters;
        for ( ;; ) {
            input->checkSignal();
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
    }

} // TechnoKeyer