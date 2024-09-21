#include "SPIBus.h"

namespace TechnoKeyer {
    SPIClass *SPIBus::_spi = new SPIClass(FSPI);

    /*
     * Start SPI
     */
    void SPIBus::begin() {
        _spi->begin(SPI_CLK_PIN,
                    -1,
                    SPI_MOSI_PIN,
                    SPI_CS_PIN);
    }

    /*
     * Get SPI Class instance
     */
    SPIClass *SPIBus::getSPI() {
        return _spi;
    }
} // TechnoKeyer
