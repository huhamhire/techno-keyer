#ifndef TUNER_CONTROL_H
#define TUNER_CONTROL_H

#include <Arduino.h>
#include <SPI.h>

#include <IO/SPIBus.h>

namespace TechnoKeyer {

    #define TUNER_CS_PIN    21

    class TunerControl {
    public:
        void begin();
        void setFrequency(uint8_t freq);

    private:
        uint32_t _spiClk = 100000; // 100 kHz
        SPIClass *_spi;

        void _setPotentiometerValue(uint8_t value);
    };

} // TechnoKeyer

#endif // TUNER_CONTROL_H
