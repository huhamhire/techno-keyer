#ifndef _VFD_1605N_
#define _VFD_1605N_

#include <Arduino.h>

#define EN_PIN      18      // Enable
#define RST_PIN     17      // Reset
#define CS_PIN      10      // SPI Chip Select
#define CLK_PIN     12      // SPI Clock
#define MOSI_PIN    11      // SPI Data

class VFD_1605N {
    public:
        void init(void);
        void setBrightness(uint16_t brightness);
        void displayChar(uint8_t row, uint8_t col, unsigned char data);
        void clear(void);

    private:
        void _sendByte(uint8_t data);
        void _setDuty(uint16_t brightness);
        void _setDisplayOff(void);
        void _setDisplayOn(void);
        
        uint8_t _delay = 16;
        bool _configLock = false;
};

#endif  // _VFD_1605N_
