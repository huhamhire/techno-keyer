#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Preferences.h>

#include <IO/RotaryEncoderInput.h>
#include <Display/DisplayContext.h>
#include <Morse/MorseEncoder.h>


namespace TechnoKeyer {
    // modes:
    //   1 - wpm
    //   2 - brightness
    #define KEYER_CONFIG_MODS 2
    #define KEYER_DISPLAY_WIDTH 16

    #define RW_MODE false
    #define RO_MODE true

    #define VFD_BRIGHTNESS_RATIO 5

    class ConfigManager {
    public:
        explicit ConfigManager(DisplayContext *display);
        void init();

        void startConfig();
        void finishConfig();
        void applyConfig();

        void setOnSpeedSet(void (* onSpeedSet)(uint8_t wpm));

    protected:
        void _initRotaryEncoder();
        void _loadFlashMemory();
        void _saveFlashMemory();

        void _onEcButtonClick();
        void _onEcValueChange(long value);

    private:
        void _setDisplayTitle(char *title);
        void _setDisplayValue(uint8_t value);

        void (* _onSpeedSet)(uint8_t speed) = [](uint8_t speed) {};

        DisplayContext *_display;
        static RotaryEncoderInput *_encoder;

        uint8_t _mode = 0;
        uint8_t _wpm = 20;
        uint16_t _bright = 100;

        Preferences _config;
    };
}

#endif  // CONFIG_H
