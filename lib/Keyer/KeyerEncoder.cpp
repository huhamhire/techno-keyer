#include <KeyerEncoder.h>


AiEsp32RotaryEncoder encoder = AiEsp32RotaryEncoder(
    ENCODER_A_PIN, 
    ENCODER_B_PIN, 
    ENCODER_BUTTON_PIN, 
    ENCODER_VCC_PIN, 
    ENCODER_STEPS
);

void IRAM_ATTR readEncoderISR() {
    encoder.readEncoder_ISR();
}


void KeyerEncoder::begin() {
    encoder.begin();
    encoder.setup(readEncoderISR);

    bool circleValues = false;
    encoder.setBoundaries(10, 30, circleValues); 

    encoder.disableAcceleration();
}

void KeyerEncoder::_onButtonClick() {
    static unsigned long lastTimePressed = 0;
    lastTimePressed = millis();
    Serial.print("button pressed ");
    Serial.print(millis());
    Serial.println(" milliseconds after restart");
}


// Check encoder status in task loop
void KeyerEncoder::check() {
    if (encoder.encoderChanged()) {
        Serial.print("Value: ");
        Serial.println(encoder.readEncoder());
    }
    if (encoder.isEncoderButtonClicked()) {
        _onButtonClick();
    }
}


// Task to check encoder status
void vEncoderCheck(void *pvParameters) {
    KeyerEncoder *keyerEncoder = (KeyerEncoder *)pvParameters;
    for (;;) {
        keyerEncoder->check();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}