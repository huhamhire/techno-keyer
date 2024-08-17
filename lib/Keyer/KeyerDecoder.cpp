#include <KeyerDecoder.h>

void KeyerDecoder::init() 
{
    _initPotentiometer();
    _initSignalInput();
}

// Initialize signal input
void KeyerDecoder::_initSignalInput() 
{
    pinMode(AUX_SIG_PIN, INPUT);
}

// Initialize potentiometer for frequency control
void KeyerDecoder::_initPotentiometer() 
{    
    spi = new SPIClass(FSPI);
    spi->begin(DEC_CLK_PIN, -1, DEC_MOSI_PIN, DEC_CS_PIN);
    pinMode(spi->pinSS(), OUTPUT);
}


// Set potentiometer value
void KeyerDecoder::_setPotentiometerValue(uint8_t value)
{
    spi->beginTransaction(SPISettings(_spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(spi->pinSS(), LOW);
    // Command
    spi->write(0x11);
    spi->write(value);
    digitalWrite(spi->pinSS(), HIGH);
    spi->endTransaction();
}


void KeyerDecoder::setValue(uint8_t value)
{
    _setPotentiometerValue(value);
}

// Check signal input
void KeyerDecoder::checkSignal()
{
    uint8_t state = digitalRead(AUX_SIG_PIN);

    if (state != _lastState) {
        uint32_t now = millis();
        _lastState = state;
        Serial.print("State -> ");
        Serial.print(state);
        Serial.print(", Time: ");
        Serial.println(now);
    }
}


// Task to check audio input signal
void vCheckAuxSignal(void *pvParameters)
{
    KeyerDecoder *decoder = (KeyerDecoder *)pvParameters;
    for (;;) {
        decoder->checkSignal();
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}
