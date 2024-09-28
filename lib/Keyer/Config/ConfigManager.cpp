#include "ConfigManager.h"

namespace TechnoKeyer {
    RotaryEncoderInput* ConfigManager::_encoder = new RotaryEncoderInput();
    ConfigStorage *ConfigManager::_storage = new ConfigStorage();

    /**
     * Constructor
     * @param display
     */
    ConfigManager::ConfigManager(DisplayContext *display)
    {
        _display = display;
    }

    /**
     * Initialize config manager
     */
    void ConfigManager::begin()
    {
        _initRotaryEncoder();
        _config = _storage->load();
        _menu = new ConfigMenu(_config);

        _onConfigSet(_config);
        _display->setBrightness(_config->bright);
    }

    /**
     * Initialize rotary encoder
     */
    void ConfigManager::_initRotaryEncoder()
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
                    nullptr);
    }

    /**
     * Set callback for on config set
     * @param callback
     */
    void ConfigManager::setOnConfig(onConfigSet callback) {
        _onConfigSet = std::move(callback);
    }

    /**
     * Set callback for on config start
     * @param callback
     */
    void ConfigManager::setOnConfigStart(onConfigEvent callback) {
        _onConfigStart = std::move(callback);
    }

    /**
     * Set callback for on config finish
     * @param callback
     */
    void ConfigManager::setOnConfigFinish(onConfigEvent callback) {
        _onConfigFinish = std::move(callback);
    }


    /**
     * Start configuration
     */
    void ConfigManager::startConfig() {
        _onConfigStart();
    }

    /**
     * Finish configuration
     */
    void ConfigManager::finishConfig()
    {
        // Apply config
        _onConfigSet(_config);
        _storage->save(_config);

        _setDisplayTitle((char*) "Config saved.");
        // Reset encoder
        _encoder->setBoundaries(0, 100);

        // Clear VFD line 1
        _display -> setValueLine((char*) "");
        vTaskDelay(800 / portTICK_PERIOD_MS);

        _onConfigFinish();

        #if DEBUG_ALL
        Serial.println("Config saved.");
        #endif
    }


    /**
     * Set title to shown on display
     * @param title
     */
    void ConfigManager::_setDisplayTitle(char *title) {
        _display->setTitleLine(_formatDisplayLine(title));
    }

    /**
     * Set value to shown on display
     * @param value
     */
    void ConfigManager::_setDisplayValue(long value) {
        char line[KEYER_DISPLAY_WIDTH] = "";
        sprintf(line, "%ld", value);
        _display->setValueLine(_formatDisplayLine(line));
    }

    /**
     * Format display line (centered)
     * @param str
     * @return
     */
    char *ConfigManager::_formatDisplayLine(char *str) {
        uint8_t width = KEYER_DISPLAY_WIDTH;
        char line[width];
        sprintf(line, "%*s%*s", (width + strlen(str)) / 2, str, (width - strlen(str)) / 2, "");
        return strdup(line);
    }


    /**
     * Handle button click
     */
    void ConfigManager::_onEcButtonClick()
    {
        if (_menu->isLast()) {
            // Finish config
            finishConfig();
            _itemIdx = -1;
        } else {
            // Config selected item
            if (_itemIdx == -1) {
                startConfig();
            }
            _itemIdx++;
        }
        _menu->selectByIdx(_itemIdx);
        // Start item config
        MenuItem* item = _menu->getItem();
        if (item == nullptr) {
            return;
        }
        _encoder->setBoundaries(item->minVal, item->maxVal);
        _encoder->setValue(item->getValue());
        // Update display
        _setDisplayTitle(item->title);
        _setDisplayValue(item->getDisplayValue());
    }

    /**
     * Handle encoder value change
     * @param value
     */
    void ConfigManager::_onEcValueChange(long value)
    {
        MenuItem* item = _menu->getItem();
        if (item == nullptr) {
            return;
        }
        item->setValue(value);
        _setDisplayValue(item->getDisplayValue());

        if (_itemIdx == 0) {
            // Preview brightness change
            _display->setBrightness(item->getDisplayValue());
        }
    }
}
