#ifndef CONFIG_MENU_H
#define CONFIG_MENU_H

#include <Arduino.h>
#include <Config/ConfigStorage.h>

namespace TechnoKeyer {
    #define CONFIG_ITEMS 4

    typedef std::function<void(long)> onConfigSetValue;
    typedef std::function<long()> onConfigGetValue;

    typedef std::function<void(long, long)> onConfigSetBoundary;

    struct MenuItem {
        char *title;
        long minVal;
        long maxVal;
        onConfigGetValue getDisplayValue;
        onConfigGetValue getValue;
        onConfigSetValue setValue;
    };

    class ConfigMenu {
    public:
        explicit ConfigMenu(Config *config);
        void selectByIdx(int8_t idx);
        MenuItem *getItem();
        bool isLast();

    private:
        int8_t _idx=-1;
        MenuItem *_items;
        Config *_config;
    };

} // TechnoKeyer

#endif // CONFIG_MENU_H
