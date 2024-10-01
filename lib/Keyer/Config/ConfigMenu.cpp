#include "ConfigMenu.h"

namespace TechnoKeyer {

    ConfigMenu::ConfigMenu(Config *config) {
        _config = config;
        _items = new MenuItem[CONFIG_ITEMS]{
                {
                        .title=(char *) "Brightness",
                        // 10~100 %
                        .minVal=1,
                        .maxVal=10,
                        .getDisplayValue=[&]() {
                            return _config->bright;
                        },
                        .getValue=[&]() {
                            return _config->bright / 10;
                        },
                        .setValue=[&](long value) {
                            _config->bright = value * 10;
                        }
                },
                {
                        .title=(char *) "TX Speed (WPM)",
                        // 10~50 WPM
                        .minVal=10,
                        .maxVal=50,
                        .getDisplayValue=[&]() {
                            return _config->tx_wpm;
                        },
                        .getValue=[&]() {
                            return _config->tx_wpm;
                        },
                        .setValue=[&](long value) {
                            _config->tx_wpm = value;
                        }
                },
                {
                        .title=(char *) "TX Tone (Hz)",
                        // 400~1000 Hz
                        .minVal=40,
                        .maxVal=100,
                        .getDisplayValue=[&]() {
                            return _config->tx_tone;
                        },
                        .getValue=[&]() {
                            return _config->tx_tone / 10;
                        },
                        .setValue=[&](long value) {
                            _config->tx_tone = value * 10;
                        }
                },
                {
                        .title=(char *) "RX Tone (Hz)",
                        // 400~1000 Hz
                        .minVal=40,
                        .maxVal=100,
                        .getDisplayValue=[&]() {
                            return _config->rx_tone;
                        },
                        .getValue=[&]() {
                            return _config->rx_tone / 10;
                        },
                        .setValue=[&](long value) {
                            _config->rx_tone = value * 10;
                        }
                }
        };

        _quickMenu = &_items[3];
    }

    /**
     * Select menu item by idx.
     * @param idx
     */
    void ConfigMenu::selectByIdx(int8_t idx) {
        if (idx < -1 || idx >= CONFIG_ITEMS) {
            return;
        }
        _idx = idx;
    }

    /**
     * Get selected menu item.
     * @return
     */
    MenuItem *ConfigMenu::getItem() {
        if (_idx >= 0 && _idx < CONFIG_ITEMS) {
            return &_items[_idx];
        } else {
            return nullptr;
        }
    }

    /**
     * Get quick menu item.
     * @return
     */
    MenuItem *ConfigMenu::getQuickMenu() {
        return _quickMenu;
    }

    /**
     * Check if current item is last.
     * @return
     */
    bool ConfigMenu::isLast() {
        return _idx == CONFIG_ITEMS - 1;
    }
} // TechnoKeyer