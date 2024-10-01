#ifndef TUNER_CONTROL_H
#define TUNER_CONTROL_H

#include <Arduino.h>
#include <SPI.h>

#include <Pinout.h>
#include <IO/SPIBus.h>

namespace TechnoKeyer {
    class TunerControl {
    public:
        void begin();
        void setPitch(uint16_t freq);

    private:
        uint32_t _spiClk = 100000; // 100 kHz
        SPIClass *_spi;

        void _setPotentiometerValue(uint8_t value);
    };

} // TechnoKeyer

#endif // TUNER_CONTROL_H
