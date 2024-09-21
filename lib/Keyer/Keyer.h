#ifndef KEYER_H
#define KEYER_H

#include <Arduino.h>
#include <SPI.h>

#include <ConfigManager.h>

#include <IO/SPIBus.h>
#include <IO/AudioInput.h>
#include <Display/DisplayContext.h>
#include <Display/DisplayObserver.h>

#include <Transmitter.h>

namespace TechnoKeyer {
    class Keyer {
    public:
        void begin();

    protected:
        void initDisplay();
        void initConfig();
        void initTransmitter();
        void initDecoder();

    private:
        static SPIBus* _spi;

        DisplayContext* _display;
        Transmitter* _transmitter;
    };
}

#endif  // KEYER_H