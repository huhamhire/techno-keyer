#ifndef _VFD_1605N_
#define _VFD_1605N_

#include <Arduino.h>
#include <SPI.h>

#define VFD_EN_PIN      17      // Enable
#define VFD_RST_PIN     18      // Reset
#define VFD_CS_PIN      10      // SPI Chip Select


class VFD_1605N {
    public:
        void init(SPIClass *spi);
        void setBrightness(uint16_t brightness);
        void displayChar(uint8_t row, uint8_t col, unsigned char data);
        void displayLine(uint8_t row, char *data);

    private:
        void _sendBytes(uint8_t* data, uint32_t size);
        void _sendCommand(uint8_t data);
        void _setDuty(uint16_t brightness);
        void _setDisplayOff();
        void _setDisplayOn();
        
        uint32_t _spiClk =  100000;     // 100kHz
        uint8_t _delay =    16;         // 16us

        SPIClass *_spi;
};

#endif  // _VFD_1605N_
