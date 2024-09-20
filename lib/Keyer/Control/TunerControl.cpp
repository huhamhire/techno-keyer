#include "TunerControl.h"

namespace KeyboardKeyer {
    /**
     * Initialize CW pitch tuner
     */
    void TunerControl::begin() {
        static SPIBus spi;
        _spi = spi.getSPI();
        pinMode(TUNER_CS_PIN, OUTPUT);
        _setPotentiometerValue(0x00);
    }

    void TunerControl::setFrequency(uint8_t freq) {
        // todo
    }

    /**
     * Set potentiometer value
     * @param value
     */
    void TunerControl::_setPotentiometerValue(uint8_t value) {
        _spi->beginTransaction(SPISettings(_spiClk, MSBFIRST, SPI_MODE0));
        digitalWrite(TUNER_CS_PIN, LOW);
        // Command
        _spi->write(0x11);
        _spi->write(value);
        digitalWrite(TUNER_CS_PIN, HIGH);
        _spi->endTransaction();
    }
} // KeyboardKeyer