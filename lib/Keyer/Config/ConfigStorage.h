#ifndef CONFIG_STORAGE_H
#define CONFIG_STORAGE_H

#include <Arduino.h>
#include <Preferences.h>

namespace TechnoKeyer {

#define RW_MODE false
#define RO_MODE true
#define CONFIG_NS "KeyerConf"

    struct Config {
        uint8_t bright;
        uint16_t tx_wpm;
        uint16_t rx_tone;
    };

    class ConfigStorage {
    public:
        Config* load();
        void save(Config *conf);

    private:
        Preferences _pref;
    };

} // TechnoKeyer

#endif //CONFIG_STORAGE_H
