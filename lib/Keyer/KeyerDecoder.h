#ifndef _KEYER_DECODER_
#define _KEYER_DECODER_

#include <Arduino.h>
#include <SPI.h>

#define DEC_CS_PIN    21
#define DEC_MOSI_PIN  11
#define DEC_CLK_PIN   12

#define AUX_SIG_PIN   8


class KeyerDecoder
{
    public:
        void init();
        void setValue(uint8_t value);
        void checkSignal();

    private:
        void _initSignalInput();
        void _initPotentiometer();
        void _setPotentiometerValue(uint8_t value);

        uint8_t _lastState = 1;
        uint32_t _spiClk = 100000; // 100 kHz
        
        SPIClass *spi;
};


void vCheckAuxSignal(void *pvParameters);

#endif  // _KEYER_DECODER_
