#ifndef _KEYER_
#define _KEYER_

#include <Arduino.h>

#include <KeyerBuffer.h>
#include <KeyerInput.h>
#include <KeyerConfig.h>
#include <KeyerDisplay.h>
#include <KeyerMorse.h>
#include <KeyerDecoder.h>
#include <KeyerWifi.h>

#include <Clock.h>

class Keyer {
    public:
        void begin();
        
    protected:
        void initDisplay();
        void initConfig();
        void initInput();
        void initOutput();
        void initClock();
        void initDecoder();

    private:
        KeyerBuffer *_buffer;
        KeyerDisplay* _display;
        KeyerConfig* _config;
        KeyerInput* _input;
        KeyerMorse* _morse;
        KeyerDecoder* _decoder;

        NTPClock* _clock;
};

#endif  // _KEYER_