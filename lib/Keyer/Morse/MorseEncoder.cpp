#include <Morse/MorseEncoder.h>

namespace TechnoKeyer {
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
            for (int i = 0; i < N_MORSE; i++) {
                if (morsetab[i].c == c) {
                    unsigned char p = morsetab[i].pat;
                    while (p != 1) {
                        if (p & 1) {
                            _sendDah();
                        } else {
                            _sendDit();
                        }
                        p = p / 2;
                    }
                    break;
                }
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