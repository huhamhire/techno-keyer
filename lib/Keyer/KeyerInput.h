#ifndef _KEYER_INPUT_
#define _KEYER_INPUT_

#include <Arduino.h>
#include <CH9350_USBKEY.h>

#include <KeyerBuffer.h>

#define SERIAL_RX_PIN 15
#define SERIAL_TX_PIN 16

#define DEBOUNCE_TIME 100

class KeyerInput {
    public:
        KeyerInput(KeyerBuffer *buffer);
        void init();
        void getKey();
    
    private:
        KeyerBuffer *_buffer;
        USB9350_KeyMouse *_usbKeyMouse;

        unsigned long _lastKeyTime = 0;
        char _lastKey = 0;
};

void vGetKey(void *pvParameters);

#endif  // _KEYER_INPUT_
