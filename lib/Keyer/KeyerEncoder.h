#ifndef _KEYER_ENCODER_
#define _KEYER_ENCODER_

#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>

#define ENCODER_A_PIN 41
#define ENCODER_B_PIN 40
#define ENCODER_BUTTON_PIN 39
#define ENCODER_VCC_PIN -1  // Direct to 3V3
#define ENCODER_STEPS 4

class KeyerEncoder {
    public:
        void begin();
        void check();

    protected:
        void _onButtonClick();
};

void vEncoderCheck(void *pvParameters);

#endif  // _KEYER_ENCODER_
