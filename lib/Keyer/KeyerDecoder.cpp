#include <KeyerDecoder.h>

void KeyerDecoder::init(SPIClass *spi)
{
    _spi = spi;
    pinMode(DEC_CS_PIN, OUTPUT);

    _initSignalInput();

    setValue(0x00);
}

// Initialize signal input
void KeyerDecoder::_initSignalInput() 
{
    pinMode(AUX_SIG_PIN, INPUT);
}


// Set potentiometer value
void KeyerDecoder::_setPotentiometerValue(uint8_t value)
{
    _spi->beginTransaction(SPISettings(_spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(DEC_CS_PIN, LOW);
    // Command
    _spi->write(0x11);
    _spi->write(value);
    digitalWrite(DEC_CS_PIN, HIGH);
    _spi->endTransaction();
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
