#ifndef VFD_1605N_H
#define VFD_1605N_H

#include <Arduino.h>
#include <SPI.h>

class VFD_1605N {
    #define VFD_BRIGHTNESS_RATIO    5

    public:
        void begin(SPIClass *spi, uint8_t en, uint8_t rst, uint8_t cs);
        void setBrightness(uint16_t brightness);
        void displayChar(uint8_t row, uint8_t col, unsigned char data);
        void displayLine(uint8_t row, char *data);

    private:
        void _sendBytes(uint8_t* data, uint32_t size);
        void _sendCommand(uint8_t data);
        void _setDuty(uint16_t brightness);
        void _setDisplayOff();
        void _setDisplayOn();

        uint8_t _enPin;
        uint8_t _rstPin;
        uint8_t _csPin;
        
        uint32_t _spiClk =  100000;     // 100kHz
        uint8_t _delay =    16;         // 16us

        SPIClass *_spi;
};

#endif  // VFD_1605N_H
