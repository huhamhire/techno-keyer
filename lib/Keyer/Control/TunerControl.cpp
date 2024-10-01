#include "TunerControl.h"

namespace TechnoKeyer {
    /**
     * Initialize CW pitch tuner
     */
    void TunerControl::begin() {
        static SPIBus spi;
        _spi = spi.getSPI();
        pinMode(TUNER_CS_PIN, OUTPUT);
        _setPotentiometerValue(0x00);
    }

    /**
     * Set CW pitch frequency
     * @param freq
     */
    void TunerControl::setPitch(uint16_t freq) {
        // Calculate potentiometer value
        double val = -0.0004 * freq * freq + 0.873 * freq - 277;
        auto valSet = (uint8_t) val;
        if (valSet >= 0x00 && valSet <= 0xCF) {
            _setPotentiometerValue(valSet);
        }

        #ifdef DEBUG_ALL
        Serial.printf("Set RX pitch: %d\n", freq);
        #endif
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
} // TechnoKeyer