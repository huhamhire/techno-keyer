#include <Morse/MorseEncoder.h>

namespace TechnoKeyer {
    MorseCodec *MorseEncoder::_codec = new MorseCodec();
    MorseBuzzer *MorseEncoder::_buzzer = new MorseBuzzer();

    /**
     * Initialize Morse Encoder
     * @param buffer
     */
    MorseEncoder::MorseEncoder(MorseOutputBuffer *buffer) {
        _buzzer->init();
        _buffer = buffer;

        pinMode(CW_PIN, OUTPUT);
    }

    /**
     *
     * @param speed
     */
    void MorseEncoder::setSpeed(uint8_t speed) {
        _speed = speed;
        _updateSpeed(speed);
    }

    /**
     * Update speed in WPM
     * @param speed
     */
    void MorseEncoder::_updateSpeed(uint8_t speed) {
        _dotTimeMs = 1200 / speed;
        _dashTimeMs = _dotTimeMs * 3;
    }

    /**
     * Send one char
     * @param c
     */
    void MorseEncoder::sendChar(char c) {
        #if DEBUG_ALL
        Serial.printf("Sending %c\n", c);
        #endif

        if (c == ' ') {
            vTaskDelay(7 * _dotTimeMs / portTICK_PERIOD_MS);
        } else {
            uint8_t code = _codec->getCode(c);
            if (code == 0) {
                return;
            }
            while (code != 1) {
                if (code & 1) {
                    _sendDah();
                } else {
                    _sendDit();
                }
                code = code / 2;
            }
            vTaskDelay(2 * _dotTimeMs / portTICK_PERIOD_MS);
        }
    }

    /**
     * Send dit
     */
    void MorseEncoder::_sendDit() {
        digitalWrite(CW_PIN, HIGH);
        _buzzer -> setOn();
        vTaskDelay(_dotTimeMs / portTICK_PERIOD_MS);

        digitalWrite(CW_PIN, LOW);
        _buzzer -> setOff();
        vTaskDelay(_dotTimeMs / portTICK_PERIOD_MS);
    }

    /**
     * Send dah
     */
    void MorseEncoder::_sendDah() {
        digitalWrite(CW_PIN, HIGH);
        _buzzer -> setOn();
        vTaskDelay(_dashTimeMs / portTICK_PERIOD_MS);

        digitalWrite(CW_PIN, LOW);
        _buzzer -> setOff();
        vTaskDelay(_dotTimeMs / portTICK_PERIOD_MS);
    }

    /**
     * Send buffer
     */
    void MorseEncoder::sendBuffer() {
        while (!_buffer->isEmpty()) {
            char c = _buffer->shift();
            sendChar(c);
        }
    }

    // Task to send morse code
    void vSendMorse(void *pvParameters) {
        MorseEncoder *morse;
        morse = (MorseEncoder *) pvParameters;

        for (;;) {
            morse->sendBuffer();
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer