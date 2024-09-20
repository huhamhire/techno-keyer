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

class Keyer {
    public:
        void begin();
        
    protected:
        void initDisplay();
        void initTransmitter();
        void initConfig();
        void initDecoder();

    private:
        TechnoKeyer::DisplayContext* _display;
        TechnoKeyer::Transmitter* _transmitter;
};

#endif  // KEYER_H