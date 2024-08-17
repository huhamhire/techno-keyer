#include <VFD_1605N.h>

// Initialize VFD
void VFD_1605N::init(SPIClass *spi)
{
    pinMode(VFD_EN_PIN, OUTPUT);
    pinMode(VFD_RST_PIN, OUTPUT);

    // Initialize SPI
    _spi = spi;
    pinMode(VFD_CS_PIN, OUTPUT);

    // Initialize VFD
    digitalWrite(VFD_EN_PIN, HIGH);

    // Reset
    delayMicroseconds(100);
    digitalWrite(VFD_RST_PIN, LOW);
    delayMicroseconds(_delay);
    digitalWrite(VFD_RST_PIN, HIGH);
    
    // Config
    _setDisplayOff();
    // Always excute before turning on
    _sendCommand(0x6C);     // set com1 to 16
    _setDuty(500);
    _setDisplayOn();
}

// Send command to VFD
void VFD_1605N::_sendCommand(uint8_t data) 
{
    _sendBytes(&data, 1);
}

// Send bytes to VFD
void VFD_1605N::_sendBytes(uint8_t *data, uint32_t size) 
{
    _spi->beginTransaction(SPISettings(_spiClk, SPI_LSBFIRST, SPI_MODE0));
    digitalWrite(VFD_CS_PIN, LOW);

    _spi->writeBytes(data, size);
    digitalWrite(VFD_CS_PIN, HIGH);

    _spi->endTransaction();
    delayMicroseconds(_delay);
}

// Send duty config to set brightness (0~1024)
void VFD_1605N::_setDuty(uint16_t brightness) 
{
    uint8_t bl, bh;
    
    bl = brightness % 4;
    bh = brightness / 4;
    
    uint8_t size = 2;
    // 0b0101_**xx, 0bxxxx_xxxx
    uint8_t buff[size] = { (uint8_t)(0x50 | bl), bh };
    _sendBytes(buff, size);
}

// Turn off VFD (Prevent malfunction for config / Blink)
void VFD_1605N::_setDisplayOff(void) 
{
    // All outputs to low
    _sendCommand(0x71);
}

// Turn on VFD
void VFD_1605N::_setDisplayOn(void)
{
    // Normal display
    _sendCommand(0x70);
}

// Set VFD brightness (0~1024)
void VFD_1605N::setBrightness(uint16_t brightness) 
{
    _setDisplayOff();
    _setDuty(brightness);
    _setDisplayOn();
}

// Display char on VFD
void VFD_1605N::displayChar(uint8_t row, uint8_t col, unsigned char data) 
{
    if ( col > 15 || row > 1) {
        // Invalid column or row
        return;
    }

    // Line1: 0x90, Line2: 0x10, 
    uint8_t line = row == 0 ? 0x90 : 0x10;
    uint8_t column = 0x0E - col;

    uint8_t size = 3;
    // line, col, char
    uint8_t buff[size] = { line, column, data };

    _sendBytes(buff, size);
}


// Display line on VFD
void VFD_1605N::displayLine(uint8_t row, char *data) 
{
    if ( row > 1) {
        // Invalid row
        return;
    }

    // Line1: 0x90, Line2: 0x10, 
    uint8_t line = row == 0 ? 0x90 : 0x10;
    
    uint8_t size = 18;
    uint8_t buff[size] = { 
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
    _sendBytes(buff, size);
}