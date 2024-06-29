#ifndef _KEYER_
#define _KEYER_

#include <Arduino.h>

#include <KeyerBuffer.h>
#include <KeyerInput.h>
#include <KeyerEncoder.h>
#include <KeyerDisplay.h>
#include <KeyerMorse.h>

class Keyer {
    public:
        void begin();

    protected:
        void initDisplay();
        void initEncorder();
        void initInput();
        void initOutput();

    private:
        KeyerBuffer *_buffer;
        KeyerDisplay* _display;
        KeyerEncoder* _encoder;
        KeyerInput* _input;
        KeyerMorse* _morse;
};

#endif  // _KEYER_