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
KeyerConfig::KeyerConfig(KeyerBuffer *buffer, KeyboardKeyer::DisplayContext *display, KeyerMorse *morse)
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

    _loadFlashMemory();
    applyConfig();
}

// Load configuration from flash memory
void KeyerConfig::_loadFlashMemory() 
{
    _config.begin("keyerConf", RO_MODE);

    _wpm = _config.getUShort("wpm", 20);
    _bright = _config.getUShort("bright", 100);

    _config.end();

    #if DEBUG_ALL
    Serial.println("Config loaded.");
    Serial.printf("  WPM: %d\n", _wpm);
    Serial.printf("  Brightness: %d\n", _bright);
    #endif
}

// Save configuration to flash memory
void KeyerConfig::_saveFlashMemory() 
{
    _config.begin("keyerConf", RW_MODE);
    _config.putUShort("wpm", _wpm);
    _config.putUShort("bright", _bright);
    _config.end();
}

// Start configuration
void KeyerConfig::startConfig() 
{
    // Clear display & sending buffer
    _buffer->clearInput();
    _buffer->clearSending();

    _display->setMode(0);

    switch (_mode) {
        // WPM
        case 1:
            _setDisplayTitle((char*) "Speed (WPM)");
            encoder.setBoundaries(10, 50, false);
            encoder.setEncoderValue(_wpm);
            _setDisplayValue(_wpm);
            break;
        // Brightness
        case 2:
            _setDisplayTitle((char*) "Brightness");
            encoder.setBoundaries(1, 10, false);
            encoder.setEncoderValue(_bright / 10);
            _setDisplayValue(_bright);
            break;
        default:
            break;
    }

    #if DEBUG_ALL
    Serial.println("Config starterd.");
    #endif
}

// Apply configuration
void KeyerConfig::applyConfig() 
{
    _morse->setSpeed(_wpm);
    _display->setBrightness(_bright * VFD_BRIGHTNESS_RATIO);
}

// Finish configuration
void KeyerConfig::finishConfig() 
{
    applyConfig();
    _saveFlashMemory();
    _setDisplayTitle((char*) "Config saved.");

    // Clear VFD line 1
    _display -> setValueLine((char*) "");
    vTaskDelay(800 / portTICK_PERIOD_MS);

    // Restore buffer to display
    _display -> setMode(1);

    // Reset encoder
    encoder.setBoundaries(0, 100, false); 

    #if DEBUG_ALL
    Serial.println("Config saved.");
    #endif
}


// Set title to shown on display
void KeyerConfig::_setDisplayTitle(char *title) 
{
    uint8_t width = KEYER_DISPLAY_WIDTH;
    char line[width] = "";
    sprintf(line, "%*s%*s", (width + strlen(title)) / 2, title, (width - strlen(title)) / 2, "");
    _display ->setTitleLine(strdup(line));
}


// Set value to shown on display
void KeyerConfig::_setDisplayValue(uint8_t value) 
{
    uint8_t width = KEYER_DISPLAY_WIDTH;
    char line[width] = "";
    sprintf(line, "%d", value);
    sprintf(line, "%*s%*s", (width + strlen(line)) / 2, strdup(line), (width - strlen(line)) / 2, "");
    _display ->setValueLine(strdup(line));
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
            break;
        // Brightness
        case 2:
            _bright = value * 10;
            _setDisplayValue(_bright);
            _display->setBrightness(_bright * VFD_BRIGHTNESS_RATIO);
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