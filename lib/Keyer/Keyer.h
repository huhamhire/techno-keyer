#ifndef KEYER_H
#define KEYER_H

#include <Arduino.h>
#include <SPI.h>

#include <KeyerConfig.h>
#include <KeyerDecoder.h>
#include <KeyerWifi.h>

#include <Display/DisplayContext.h>
#include <Display/DisplayObserver.h>

#include <Transmitter.h>

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
        void initTransmitter();
        void initConfig();
        void initClock();
        void initDecoder();

    private:
        KeyboardKeyer::DisplayContext* _display;
        KeyerConfig* _config;
        KeyboardKeyer::Transmitter* _transmitter;
        KeyerDecoder* _decoder;

        NTPClock* _clock;

        SPIClass *_spi;
};

#endif  // KEYER_H