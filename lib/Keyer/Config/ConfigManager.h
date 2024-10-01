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
        void checkQuickConfig();

        void setOnConfig(onConfigSet callback);
        void setOnConfigStart(onConfigEvent callback);
        void setOnConfigFinish(onConfigEvent callback);
        void setOnQuickConfig(onConfigSet callback);
        void setOnQuickConfigFinish(onConfigEvent callback);

    protected:
        void _initRotaryEncoder();

        void _onEcButtonClick();
        void _onEcValueChange(long value);

    private:
        void _setupQuickConfig();
        void _setDisplayTitle(char *title);
        void _setDisplayValue(long value);
        char* _formatDisplayLine(char* str);

        onConfigSet _onConfigSet = [](Config* conf) {};
        onConfigEvent _onConfigStart = []() {};
        onConfigEvent _onConfigFinish = []() {};

        onConfigSet _onQuickConfig = [](Config* conf) {};
        onConfigEvent _onQuickConfigFinish = []() {};

        Config *_config = nullptr;
        ConfigMenu *_menu = nullptr;
        DisplayContext *_display;

        static RotaryEncoderInput *_encoder;
        static ConfigStorage *_storage;

        bool _inQuickConfig = false;
        unsigned long _lastQuickConfigTime = 0;
        int8_t _itemIdx = -1;
    };

    [[noreturn]] void vCheckQuickConfig(void *pvParameters);
}

#endif  // CONFIG_H
