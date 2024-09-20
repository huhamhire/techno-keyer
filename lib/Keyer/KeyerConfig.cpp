#include <KeyerConfig.h>

namespace KeyboardKeyer {
    RotaryEncoderInput* KeyerConfig::_encoder = new RotaryEncoderInput();

    // Config Constructcor
    KeyerConfig::KeyerConfig(DisplayContext *display)
    {
        _display = display;
    }

    // Initialize configurator
    void KeyerConfig::init()
    {
        _initRotaryEncoder();
        _loadFlashMemory();
        applyConfig();
    }


    void KeyerConfig::_initRotaryEncoder()
    {
        _encoder->begin();
        _encoder->setOnButtonClicked([&]() {
            _onEcButtonClick();
        });
        _encoder->setOnValueChanged([&](long value) {
            _onEcValueChange(value);
        });
        xTaskCreate(vCheckRotaryEncoder,
                    "vCheckRotaryEncoder",
                    2048,
                    _encoder,
                    1,
                    NULL);
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
        _display->setMode(0);

        switch (_mode) {
            // WPM
            case 1:
                _setDisplayTitle((char*) "Speed (WPM)");
                _encoder->setBoundaries(10, 50);
                _encoder->setValue(_wpm);
                _setDisplayValue(_wpm);
                break;
            // Brightness
            case 2:
                _setDisplayTitle((char*) "Brightness");
                _encoder->setBoundaries(1, 10);
                _encoder->setValue(_bright / 10);
                _setDisplayValue(_bright);
                break;
            default:
                break;
        }

        #if DEBUG_ALL
        Serial.println("Config starterd.");
        #endif
    }

    void KeyerConfig::setOnSpeedSet(void (* onSpeedSet)(uint8_t wpm))
    {
        _onSpeedSet = onSpeedSet;
    }

    // Apply configuration
    void KeyerConfig::applyConfig()
    {
        _onSpeedSet(_wpm);
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
        _encoder->setBoundaries(0, 100);

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
}
