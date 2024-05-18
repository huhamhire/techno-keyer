#include <KeyerMorse.h>

// KeyerMorse Sender Constructor
KeyerMorse::KeyerMorse(KeyerBuffer* buffer) {
    _buffer = buffer;
    _speed = 20;
}

// Initialize the keyer
void KeyerMorse::begin() {
    pinMode(CW_PIN, OUTPUT);
    digitalWrite(CW_PIN, 0);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 0);

    _updateSpeed();
}

// Set speed in WPM
void KeyerMorse::setSpeed(int speed) {
    _speed = speed;
    _updateSpeed();
}

// Update speed in WPM
void KeyerMorse::_updateSpeed() {
    // https://k7mem.com/Keyer_Speed.html
    _dot_len = (1200 / _speed);
    _dash_len = (3 * (1200 / _speed));
}

// Send dit
void KeyerMorse::_sendDit() {
    digitalWrite(LED_PIN, 1);
    digitalWrite(CW_PIN, 1);
    vTaskDelay(_dot_len / portTICK_PERIOD_MS);

    digitalWrite(LED_PIN, 0);
    digitalWrite(CW_PIN, 0);
    vTaskDelay(_dot_len / portTICK_PERIOD_MS);
}

// Send dah
void KeyerMorse::_sendDah() {
    digitalWrite(LED_PIN, 1);
    digitalWrite(CW_PIN, 1);
    vTaskDelay(_dash_len / portTICK_PERIOD_MS);

    digitalWrite(LED_PIN, 0);
    digitalWrite(CW_PIN, 0);
    vTaskDelay(_dot_len / portTICK_PERIOD_MS);
}

// Send one char
void KeyerMorse::sendChar(char c) {
    Serial.printf("Sending %c\n", c);
    if (c == ' ') {
        vTaskDelay(7 * _dot_len / portTICK_PERIOD_MS);
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
        vTaskDelay(2 * _dot_len / portTICK_PERIOD_MS);
    }
}

// Send whole buffer content
void KeyerMorse::sendBuffer() {
    while (!_buffer->isSendingEmpty()) {
        sendChar(_buffer->getFirstSendingChar());
        _buffer->unshiftSending();
    }
}


// Task to send morse code
void vSendMorse(void *pvParameters) {
    KeyerMorse *morse;
    morse = (KeyerMorse *)pvParameters;

    for ( ;; ) {
        morse->sendBuffer();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}
