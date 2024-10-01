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

        // Quick menu
        _setupQuickConfig();
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
        _encoder->setOnButtonLongPressed([&]() {
            // Clean reset
            ESP.restart();
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
     * Set callback for on quick config
     * @param callback
     */
    void ConfigManager::setOnQuickConfig(onConfigSet callback) {
        _onQuickConfig = std::move(callback);
    }

    /**
     * Set callback for on quick config finish
     * @param callback
     */
    void ConfigManager::setOnQuickConfigFinish(onConfigEvent callback) {
        _onQuickConfigFinish = std::move(callback);
    }


    /**
     * Start configuration
     */
    void ConfigManager::startConfig() {
        _onConfigStart();
        _inQuickConfig = false;
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

        // Reset encoder to quick config mode
        _setupQuickConfig();

        // Clear VFD line 1
        _display -> setValueLine((char*) "");
        vTaskDelay(800 / portTICK_PERIOD_MS);

        _onConfigFinish();

        _inQuickConfig = false;

        #if DEBUG_ALL
        Serial.println("Config saved.");
        #endif
    }

    /**
     * Check quick config
     */
    void ConfigManager::checkQuickConfig() {
        unsigned long now = millis();
        if (now - _lastQuickConfigTime > 3000 && _inQuickConfig) {
            _onQuickConfigFinish();
            _inQuickConfig = false;
        }
    }


    /**
     * Setup quick config
     */
    void ConfigManager::_setupQuickConfig() {
        MenuItem *item = _menu->getQuickMenu();
        _encoder->setBoundaries(item->minVal, item->maxVal);
        _encoder->setValue(item->getValue());
    }

    /**
     * Set title to shown on display
     * @param title
     */
    void ConfigManager::_setDisplayTitle(char *title) {
        char* line = _formatDisplayLine(title);
        _display->setTitleLine(line);
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
            item = _menu->getQuickMenu();
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
        bool isQuickMenu = item == nullptr;
        if (isQuickMenu) {
            // Quick menu mode
            item = _menu->getQuickMenu();
            item->setValue(value);
            _setDisplayTitle(item->title);
            _onQuickConfig(_config);
            _inQuickConfig = true;
            _lastQuickConfigTime = millis();
        } else {
            // Normal config
            item->setValue(value);
        }
        _setDisplayValue(item->getDisplayValue());

        if (_itemIdx == 0) {
            // Preview brightness change
            _display->setBrightness(item->getDisplayValue());
        }
    }

    /**
     * Check quick config state
     * @param pvParameters
     */
    void vCheckQuickConfig(void *pvParameters) {
        ConfigManager *config;
        config = (ConfigManager *) pvParameters;
        for (;;) {
            config->checkQuickConfig();
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }
}
