#ifndef _VFD_1605N_
#define _VFD_1605N_

#include <Arduino.h>

#define EN_PIN      18      // 启用
#define RST_PIN     17      // RESET
#define CS_PIN      10      // SPI 片选
#define CLK_PIN     12      // SPI 时钟
#define MOSI_PIN    11      // SPI 数据

class VFD_1605N {
    public:
        void init(void);
        void setBrightness(unsigned short brightness);
        void clear(void);
        void displayChar(unsigned char row, unsigned char col, unsigned char data);

    protected:
        void sendByte(uint8_t data);
        
        uint8_t _delay = 16;
};

#endif  // _VFD_1605N_
