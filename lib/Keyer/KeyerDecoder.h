#ifndef _KEYER_DECODER_
#define _KEYER_DECODER_

#include <Arduino.h>
#include <SPI.h>

#define DEC_CS_PIN    21


class KeyerDecoder
{
    public:
        void init(SPIClass *spi);
        void setValue(uint8_t value);

    private:
        void _initSignalInput();
        void _setPotentiometerValue(uint8_t value);

        uint32_t _spiClk = 100000; // 100 kHz
        
        SPIClass *_spi;
};


void vCheckAuxSignal(void *pvParameters);

#endif  // _KEYER_DECODER_
