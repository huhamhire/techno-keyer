#include "SPIBus.h"

namespace KeyboardKeyer {
    SPIClass *SPIBus::_spi = new SPIClass(FSPI);

    /*
     * Start SPI
     */
    void SPIBus::begin() {
        _spi->begin(SPI_CS_PIN, SPI_CLK_PIN, SPI_MOSI_PIN);
    }

    /*
     * Get SPI Class instance
     */
    SPIClass *SPIBus::getSPI() {
        return _spi;
    }
} // KeyboardKeyer
