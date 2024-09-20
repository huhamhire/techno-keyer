#ifndef SPI_BUS_H
#define SPI_BUS_H

#include <Arduino.h>
#include <SPI.h>

namespace KeyboardKeyer {

    #define SPI_CS_PIN      10      // SPI Chip Select
    #define SPI_CLK_PIN     12      // SPI Clock
    #define SPI_MOSI_PIN    11      // SPI Data

    class SPIBus {
    public:
        void begin();
        SPIClass* getSPI();

    private:
        static SPIClass *_spi;
    };

} // KeyboardKeyer

#endif // SPI_BUS_H
