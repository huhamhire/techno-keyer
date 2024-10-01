#include "RotaryEncoderInput.h"

#include <utility>

namespace TechnoKeyer {

    /**
     * Encoder ISR callback
     */
    void IRAM_ATTR readEncoderISR()
    {
        RotaryEncoderInput::getEncoder()->readEncoder_ISR();
    }

    AiEsp32RotaryEncoder *RotaryEncoderInput::_ec = new AiEsp32RotaryEncoder(
            ENCODER_A_PIN,
            ENCODER_B_PIN,
            ENCODER_BUTTON_PIN,
            ENCODER_VCC_PIN,
            ENCODER_STEPS);

    /**
     * Start rotary encoder
     */
    void RotaryEncoderInput::begin() {
        _ec->begin();
        _ec->setup(readEncoderISR);
        _ec->disableAcceleration();
    }

    /***
     * Check encoder status on loop
     */
    void RotaryEncoderInput::checkEncoder() {
        if (_ec->encoderChanged()) {
            _onValueChanged(_ec->readEncoder());
        }

        if (!_isButtonDown) {
            if (_ec->isEncoderButtonDown()) {
                _isButtonDown = true;
                _lastButtonDownTime = millis();
            }
        } else {
            unsigned long duration = millis() - _lastButtonDownTime;
            if (_ec->isEncoderButtonDown()) {
                if (duration > 3000) {
                    _onButtonLongPressed();
                }
            } else {
                // debounce
                if (duration > 30) {
                    _onButtonClicked();
                }
                _isButtonDown = false;
                _lastButtonDownTime = 0;
            }
        }
    }

    /**
     * Set encoder value
     * @param value
     */
    void RotaryEncoderInput::setValue(long value) {
        _ec->setEncoderValue(value);
    }

    /**
     * Get encoder boundary
     * @param min
     * @param max
     */
    void RotaryEncoderInput::setBoundaries(long min, long max) {
        _ec->setBoundaries(min, max, false);
    }

    /**
     * Set on value changed callback
     * @param callback
     */
    void RotaryEncoderInput::setOnValueChanged(onValueChanged callback) {
        _onValueChanged = std::move(callback);
    }

    /**
     * Set on button clicked callback
     * @param callback
     */
    void RotaryEncoderInput::setOnButtonClicked(onButtonClicked callback) {
        _onButtonClicked = std::move(callback);
    }

    /**
     * Set on button long pressed callback
     * @param callback
     */
    void RotaryEncoderInput::setOnButtonLongPressed(onButtonClicked callback) {
        _onButtonLongPressed = std::move(callback);
    }

    /**
     * Get rotary encoder instance
     * @return
     */
    AiEsp32RotaryEncoder *RotaryEncoderInput::getEncoder() {
        return _ec;
    }

    /**
     * Check rotary encoder status
     * @param pvParameters
     */
    void vCheckRotaryEncoder(void *pvParameters) {
        auto *encoderInput = (RotaryEncoderInput *)pvParameters;
        for (;;) {
            encoderInput->checkEncoder();
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer