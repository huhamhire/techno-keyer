#ifndef _KEYER_
#define _KEYER_

#include <Arduino.h>
#include <SPI.h>

#include <KeyerBuffer.h>
#include <KeyerInput.h>
#include <KeyerConfig.h>
#include <KeyerDisplay.h>
#include <KeyerMorse.h>
#include <KeyerDecoder.h>
#include <KeyerWifi.h>

#include <Clock.h>

#define SPI_CS_PIN      10      // SPI Chip Select
#define SPI_CLK_PIN     12      // SPI Clock
#define SPI_MOSI_PIN    11      // SPI Data


class Keyer {
    public:
        void begin();
        
    protected:
        void _initSPI();
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

        SPIClass *_spi;
};

#endif  // _KEYER_