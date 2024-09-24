#ifndef SPI_BUS_H
#define SPI_BUS_H

#include <Arduino.h>
#include <Pinout.h>
#include <SPI.h>

namespace TechnoKeyer {
    class SPIBus {
    public:
        void begin();
        SPIClass* getSPI();

    private:
        static SPIClass *_spi;
    };

} // TechnoKeyer

#endif // SPI_BUS_H
