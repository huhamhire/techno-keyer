#include <KeyerConfig.h>


AiEsp32RotaryEncoder encoder = AiEsp32RotaryEncoder(
    ENCODER_A_PIN, 
    ENCODER_B_PIN, 
    ENCODER_BUTTON_PIN, 
    ENCODER_VCC_PIN, 
    ENCODER_STEPS
);

void IRAM_ATTR readEncoderISR() 
{
    encoder.readEncoder_ISR();
}

// Config Constructcor
KeyerConfig::KeyerConfig(KeyerBuffer *buffer, KeyerDisplay *display, KeyerMorse *morse) 
{
    _buffer = buffer;
    _display = display;
    _morse = morse;
}

// Initialize configurator
void KeyerConfig::init() 
{
    encoder.begin();
    encoder.setup(readEncoderISR);

    encoder.disableAcceleration();
}

// Start configuration
void KeyerConfig::startConfig() 
{
    // Clear display & sending buffer
    _buffer->clearInput();
    _buffer->clearSending();

    switch (_mode) {
        // WPM
        case 1:
            _setDisplayTitle("Speed (WPM)");
            encoder.setBoundaries(10, 50, false);

            _wpm = _morse->getSpeed();
            encoder.setEncoderValue(_wpm);
            _setDisplayValue(_wpm);
            break;
        default:
            break;
    }

    #if DEBUG_ALL
    Serial.println("Config starterd.");
    #endif
}

// Finish configuration
void KeyerConfig::finishConfig() 
{
    _setDisplayTitle("Config saved.");
    _display->setVFDLine(1, "");

    vTaskDelay(800 / portTICK_PERIOD_MS);

    // Restore buffer to display
    _display->setVFDLine(0, _buffer->getSending());
    _display->setVFDLine(1, _buffer->getInput());

    // Reset encoder
    encoder.setBoundaries(0, 100, false); 

    #if DEBUG_ALL
    Serial.println("Config finished.");
    #endif
}


// Set title to shown on display
void KeyerConfig::_setDisplayTitle(char *title) 
{
    uint8_t width = KEYER_DISPLAY_WIDTH;
    char line[width] = "";
    sprintf(line, "%*s%*s", (width + strlen(title)) / 2, title, (width - strlen(title)) / 2, "");
    _display->setVFDLine(0, strdup(line));
}


// Set value to shown on display
void KeyerConfig::_setDisplayValue(uint8_t value) 
{
    uint8_t width = KEYER_DISPLAY_WIDTH;
    char line[width] = "";
    sprintf(line, "%d", value);
    sprintf(line, "%*s%*s", (width + strlen(line)) / 2, strdup(line), (width - strlen(line)) / 2, "");
    _display->setVFDLine(1, strdup(line));
}


// Handle button click
void KeyerConfig::_onEcButtonClick() 
{
    _mode += 1;
    if (_mode > KEYER_CONFIG_MODS) {
        _mode = 0;
    }
    if (_mode == 0) {
        finishConfig();
    } else {
        startConfig();
    }
}

// Handle encoder value change
void KeyerConfig::_onEcValueChange(long value)
{
    switch (_mode) {
        // WPM
        case 1:
            _wpm = value;
            _setDisplayValue(_wpm);
            _morse->setSpeed(_wpm);
            break;
        default:
            break;
    }
}


// Check encoder status in task loop
void KeyerConfig::checkEncoder() 
{
    if (encoder.encoderChanged()) {
        _onEcValueChange(encoder.readEncoder());
    }
    if (encoder.isEncoderButtonClicked()) {
        _onEcButtonClick();
    }
}


// Task to check encoder status
void vEncoderCheck(void *pvParameters)
{
    KeyerConfig *keyerConfig = (KeyerConfig *)pvParameters;
    for (;;) {
        keyerConfig->checkEncoder();
        vTaskDelay(20 / portTICK_PERIOD_MS);
    }
}