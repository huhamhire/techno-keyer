#include <VFD_1605N.h>

// Initialize VFD
void VFD_1605N::init(void)
{
    pinMode(EN_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);

    // Initialize SPI
    spi = new SPIClass(FSPI);
    spi->begin(CLK_PIN, -1, MOSI_PIN, CS_PIN);
    pinMode(spi->pinSS(), OUTPUT);

    // Initialize VFD
    digitalWrite(EN_PIN, HIGH);

    // Reset
    delayMicroseconds(100);
    digitalWrite(RST_PIN, LOW);
    delayMicroseconds(_delay);
    digitalWrite(RST_PIN, HIGH);
    
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
    spi->beginTransaction(SPISettings(_spiClk, LSBFIRST, SPI_MODE0));
    digitalWrite(spi->pinSS(), LOW);
    spi->writeBytes(data, size);
    digitalWrite(spi->pinSS(), HIGH);

    spi->endTransaction();
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
