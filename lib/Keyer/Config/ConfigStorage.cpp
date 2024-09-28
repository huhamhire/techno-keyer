#include "ConfigStorage.h"

namespace TechnoKeyer {
    /**
     * Load config from storage
     * @return
     */
    Config *ConfigStorage::load() {
        Config *conf = new Config();

        _pref.begin(CONFIG_NS, RO_MODE);

        conf->bright = _pref.getUChar("bright", 100);
        conf->tx_wpm = _pref.getUChar("tx_wpm", 20);
        conf->rx_tone = _pref.getUShort("rx_tone", 600);

        _pref.end();

        #if DEBUG_ALL
        Serial.println("Config loaded.");
        Serial.printf("  Brightness: %d\n", conf->bright);
        Serial.printf("  TX WPM: %d\n", conf->tx_wpm);
        Serial.printf("  RX Tone: %d\n", conf->rx_tone);
        #endif

        return conf;
    }

    /**
     * Save config to storage
     * @param conf
     */
    void ConfigStorage::save(Config *conf) {
        _pref.begin(CONFIG_NS, RW_MODE);

        _pref.putUChar("bright", conf->bright);
        _pref.putUChar("tx_wpm", conf->tx_wpm);
        _pref.putUShort("rx_tone", conf->rx_tone);

        _pref.end();
    }
} // TechnoKeyer