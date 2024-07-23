#include <VFD_1605N.h>

// Initialize VFD
void VFD_1605N::init(void)
{
    pinMode(EN_PIN, OUTPUT);
    pinMode(RST_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);

    // initialize VFD
    digitalWrite(EN_PIN, HIGH);
    digitalWrite(CS_PIN, HIGH);

    // Reset
    delayMicroseconds(100);
    digitalWrite(RST_PIN, LOW);
    delayMicroseconds(_delay);
    digitalWrite(RST_PIN, HIGH);
    
    // Lock for config
    _configLock = true;
    _setDisplayOff();       

    digitalWrite(CS_PIN, LOW);
    _sendByte(0x6C);        // set com1-com16
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);

    _setDuty(500);
    clear();                // clear display

    // Unlock for config
    _configLock = false;
    _setDisplayOn();        // normal display
}

// Send byte to VFD
void VFD_1605N::_sendByte(uint8_t data) 
{
    for (int i = 0; i < 8; i++) {
        digitalWrite(CLK_PIN, LOW);

        if ( data & 0x01 ) {
            digitalWrite(MOSI_PIN, HIGH);
        } else {
            digitalWrite(MOSI_PIN, LOW);
        }
        data = data >> 1;
        delayMicroseconds(_delay);

        digitalWrite(CLK_PIN, HIGH);
        delayMicroseconds(_delay);
    }
}

// Send duty config to set brightness (0~1024)
void VFD_1605N::_setDuty(uint16_t brightness) 
{
    uint8_t bl, bh;
    
    bl = brightness % 4;
    bh = brightness / 4;
    
    digitalWrite(CS_PIN, LOW);
    // 0b0101_**xx
    _sendByte(0x50 | bl);
    // 0bxxxx_xxxx
    _sendByte(bh);
    digitalWrite(CS_PIN, HIGH);
    
    delayMicroseconds(_delay);
}

// Turn off VFD (Prevent malfunction for config / Blink)
void VFD_1605N::_setDisplayOff(void) 
{
    digitalWrite(CS_PIN, LOW);
    // All outputs to low
    _sendByte(0x71);
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
}

// Turn on VFD
void VFD_1605N::_setDisplayOn(void)
{
    digitalWrite(CS_PIN, LOW);
    // Normal display
    _sendByte(0x70);
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
}

void VFD_1605N::clear(void) 
{
    digitalWrite(CS_PIN, LOW);
    // Line 1
    _sendByte(0x90);
    _sendByte(0x00);
    for (int i = 0; i < 16; i++) {
        _sendByte(0xff);
    }
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);

    digitalWrite(CS_PIN, LOW);
    // Line 2
    _sendByte(0x10);
    _sendByte(0x00);
    for (int i = 0; i < 16; i++) {
        _sendByte(0xff);
    }
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
}

// Set VFD brightness (0~1024)
void VFD_1605N::setBrightness(uint16_t brightness) 
{
    _configLock = true;
    _setDisplayOff();

    _setDuty(brightness);

    _setDisplayOn();
    _configLock = false;
}

// Display char on VFD
void VFD_1605N::displayChar(uint8_t row, uint8_t col, unsigned char data) 
{
    if (_configLock) {
        // Skip while config locked
        return;
    }
    digitalWrite(CS_PIN, LOW);
    
    // Select line
    if (row == 0) {
        // Line 2
        _sendByte(0x10);
    } else if (row == 1) {
        // Line 1
        _sendByte(0x90);
    } else {
        // Exit
        digitalWrite(CS_PIN, HIGH);
        delayMicroseconds(_delay);
        return;
    }
    
    if (col > 15) {
        // Exit
        digitalWrite(CS_PIN, HIGH);
        delayMicroseconds(_delay);
        return;
    }
    
    _sendByte(15 - col);
    _sendByte(data);
    
    digitalWrite(CS_PIN, HIGH);
    delayMicroseconds(_delay);
    return;
}
