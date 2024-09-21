#include "RotaryEncoderInput.h"

namespace TechnoKeyer {
    AiEsp32RotaryEncoder *RotaryEncoderInput::_ec = new AiEsp32RotaryEncoder(
            ENCODER_A_PIN,
            ENCODER_B_PIN,
            ENCODER_BUTTON_PIN,
            ENCODER_VCC_PIN,
            ENCODER_STEPS);

    /**
     *
     */
    void RotaryEncoderInput::begin() {
        _ec->begin();
        _ec->setup([]() {
            _ec->readButton_ISR();
        });
        _ec->disableAcceleration();
    }

    void RotaryEncoderInput::checkEncoder() {

    }

    void RotaryEncoderInput::setValue(long value) {
        _ec->setEncoderValue(value);
    }

    void RotaryEncoderInput::setBoundaries(long min, long max) {
        _ec->setBoundaries(min, max, false);
    }

    void RotaryEncoderInput::setOnValueChanged(std::function<void(long)> onValueChanged) {
        _onValueChanged = onValueChanged;
    }

    void RotaryEncoderInput::setOnButtonClicked(std::function<void()> onButtonClicked) {
        _onButtonClicked = onButtonClicked;
    }

    void vCheckRotaryEncoder(void *pvParameters) {
        RotaryEncoderInput *encoderInput = (RotaryEncoderInput *)pvParameters;
        for (;;) {
            encoderInput->checkEncoder();
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer