#include <KeyerDecoder.h>

void KeyerDecoder::init(SPIClass *spi)
{
    _spi = spi;
    pinMode(DEC_CS_PIN, OUTPUT);
    setValue(0x00);
}

// Set potentiometer value
void KeyerDecoder::_setPotentiometerValue(uint8_t value)
{
    _spi->beginTransaction(SPISettings(_spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(DEC_CS_PIN, LOW);
    // Command
    _spi->write(0x11);
    _spi->write(value);
    digitalWrite(DEC_CS_PIN, HIGH);
    _spi->endTransaction();
}


void KeyerDecoder::setValue(uint8_t value)
{
    _setPotentiometerValue(value);
}

