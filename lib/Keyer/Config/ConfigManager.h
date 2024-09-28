#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

#include "IO/RotaryEncoderInput.h"
#include "Display/DisplayContext.h"
#include "ConfigStorage.h"
#include "ConfigMenu.h"


namespace TechnoKeyer {
    #define KEYER_DISPLAY_WIDTH     16

    typedef std::function<void(Config*)> onConfigSet;
    typedef std::function<void()> onConfigEvent;

    class ConfigManager {
    public:
        explicit ConfigManager(DisplayContext *display);
        void begin();

        void startConfig();
        void finishConfig();

        void setOnConfig(onConfigSet callback);
        void setOnConfigStart(onConfigEvent callback);
        void setOnConfigFinish(onConfigEvent callback);

    protected:
        void _initRotaryEncoder();

        void _onEcButtonClick();
        void _onEcValueChange(long value);

    private:
        void _setDisplayTitle(char *title);
        void _setDisplayValue(long value);
        char* _formatDisplayLine(char* str);

        onConfigSet _onConfigSet = [](Config* conf) {};
        onConfigEvent _onConfigStart = []() {};
        onConfigEvent _onConfigFinish = []() {};

        Config *_config = nullptr;
        ConfigMenu *_menu = nullptr;
        DisplayContext *_display;

        static RotaryEncoderInput *_encoder;
        static ConfigStorage *_storage;

        int8_t _itemIdx = -1;
    };
}

#endif  // CONFIG_H
