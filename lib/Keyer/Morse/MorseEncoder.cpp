#include <Morse/MorseEncoder.h>

#include <utility>

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
    }

    /**
     * Send one char
     * @param c
     */
    void MorseEncoder::sendChar(char c) {
        #if DEBUG_ALL
        Serial.printf("Sending %c\n", c);
        #endif

        _onMorseSent();
        if (c == ' ') {
            vTaskDelay(7 * _dotTimeMs / portTICK_PERIOD_MS);
        } else {
            uint8_t code = _codec->getCode(c);
            while (code != 1) {
                if (code & 1) {
                    _sendSignal(DAH);
                } else {
                    _sendSignal(DIT);
                }
                code = code >> 1;
            }
            vTaskDelay(2 * _dotTimeMs / portTICK_PERIOD_MS);
        }
    }


    /**
     * Set callback on morse sent
     * @param callback
     */
    void MorseEncoder::setOnMorseSent(onMorseSent callback) {
        _onMorseSent = std::move(callback);
    }


    /**
     * Send morse signal
     * @param sig
     */
    void MorseEncoder::_sendSignal(uint8_t sig) {
        uint16_t sigTimeMs = sig == DIT ?
                _dotTimeMs : _dotTimeMs * 3;

        digitalWrite(CW_PIN, HIGH);
        _buzzer -> setOn();
        vTaskDelay(sigTimeMs / portTICK_PERIOD_MS);

        digitalWrite(CW_PIN, LOW);
        _buzzer -> setOff();
        vTaskDelay(_dotTimeMs / portTICK_PERIOD_MS);
    }


    /**
     * Send buffer
     */
    void MorseEncoder::sendBuffer() {
        while (!_buffer->isEmpty()) {
            char c = _buffer->first();
            sendChar(c);
            _buffer->shift();
        }
    }

    /**
     * Task to send morse code
     * @param pvParameters
     */
    void vSendMorse(void *pvParameters) {
        MorseEncoder *morse;
        morse = (MorseEncoder *) pvParameters;

        for (;;) {
            morse->sendBuffer();
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }
} // TechnoKeyer