#include <VFD_1605N.h>

/**
 * Initialize VFD
 * @param spi
 */

void VFD_1605N::begin(SPIClass *spi, uint8_t en, uint8_t rst, uint8_t cs)
{
    _enPin = en;
    _rstPin = rst;
    _csPin = cs;

    pinMode(_enPin, OUTPUT);
    pinMode(_rstPin, OUTPUT);

    // Initialize SPI
    _spi = spi;
    pinMode(_csPin, OUTPUT);

    // Initialize VFD
    digitalWrite(_enPin, HIGH);

    // Reset
    delayMicroseconds(100);
    digitalWrite(_rstPin, LOW);
    delayMicroseconds(_delay);
    digitalWrite(_rstPin, HIGH);
    
    // Config
    _setDisplayOff();
    // Always execute before turning on
    _sendCommand(0x6C);     // set com1 to 16
    _setDuty(500);
    _setDisplayOn();
}

/**
 * Send command to VFD
 * @param data
 */
void VFD_1605N::_sendCommand(uint8_t data) 
{
    _sendBytes(&data, 1);
}

/**
 * Send bytes to VFD
 * @param data
 * @param size
 */
void VFD_1605N::_sendBytes(uint8_t *data, uint32_t size) 
{
    _spi->beginTransaction(SPISettings(_spiClk, SPI_LSBFIRST, SPI_MODE0));
    digitalWrite(_csPin, LOW);

    _spi->writeBytes(data, size);
    digitalWrite(_csPin, HIGH);

    _spi->endTransaction();

    delayMicroseconds(_delay);
}

/**
 * Send duty config to set brightness (0~1024)
 * @param brightness
 */
void VFD_1605N::_setDuty(uint16_t brightness) 
{
    uint8_t bl, bh;
    
    bl = brightness % 4;
    bh = brightness / 4;

    // 0b0101_**xx, 0bxxxx_xxxx
    uint8_t buff[2] = { (uint8_t)(0x50 | bl), bh };
    _sendBytes(buff, 2);
}

/**
 * Turn off VFD (Prevent malfunction for config / Blink)
 */
void VFD_1605N::_setDisplayOff()
{
    // All outputs to low
    _sendCommand(0x71);
}

/**
 * Turn on VFD
 */
void VFD_1605N::_setDisplayOn()
{
    // Normal display
    _sendCommand(0x70);
}

/**
 * Set VFD brightness (0~1024)
 * @param brightness
 */
void VFD_1605N::setBrightness(uint16_t brightness) 
{
    _setDisplayOff();
    _setDuty(brightness);
    _setDisplayOn();
}

/**
 * Display char on VFD
 * @param row
 * @param col
 * @param data
 */
void VFD_1605N::displayChar(uint8_t row, uint8_t col, unsigned char data) 
{
    if ( col > 15 || row > 1) {
        // Invalid column or row
        return;
    }

    // Line1: 0x90, Line2: 0x10, 
    uint8_t line = row == 0 ? 0x90 : 0x10;
    uint8_t column = 0x0E - col;

    // line, col, char
    uint8_t buff[3] = { line, column, data };

    _sendBytes(buff, 3);
}


/**
 * Display line on VFD
 * @param row
 * @param data
 */
void VFD_1605N::displayLine(uint8_t row, char *data) 
{
    if (row > 1) {
        // Invalid row
        return;
    }

    // Line1: 0x90, Line2: 0x10, 
    uint8_t line = row == 0 ? 0x90 : 0x10;

    uint8_t buff[18] = {
        line, 0x00,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    };
    // Fill data
    for (uint8_t i = 0; i < 16; i++) {
        uint8_t c = data[i];
        if (c == 0x00) {
            // End of string
            break;
        }
        buff[2 + (15 - i)] = c;
    }

    _sendBytes(buff, 18);
}