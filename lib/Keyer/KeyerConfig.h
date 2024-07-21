#ifndef _KEYER_CONFIG_
#define _KEYER_CONFIG_

#include <Arduino.h>
#include <AiEsp32RotaryEncoder.h>
#include <Preferences.h>

#include <KeyerBuffer.h>
#include <KeyerDisplay.h>
#include <KeyerMorse.h>

#define ENCODER_A_PIN 41
#define ENCODER_B_PIN 40
#define ENCODER_BUTTON_PIN 39
#define ENCODER_VCC_PIN -1  // Direct to 3V3
#define ENCODER_STEPS 4

// modes:
//   1 - wpm
#define KEYER_CONFIG_MODS 1
#define KEYER_DISPLAY_WIDTH 16

#define RW_MODE false
#define RO_MODE true

class KeyerConfig 
{
    public:
        KeyerConfig(KeyerBuffer *buffer, KeyerDisplay *display, KeyerMorse *morse);
        void init();
        void checkEncoder();

        void startConfig();
        void finishConfig();
        void applyConfig();

    protected:
        void _loadFlashMemory();
        void _saveFlashMemory();

        void _onEcButtonClick();
        void _onEcValueChange(long value);

    private:
        void _setDisplayTitle(char *title);
        void _setDisplayValue(uint8_t value);

        KeyerBuffer *_buffer;
        KeyerDisplay *_display;
        KeyerMorse *_morse;

        uint8_t _mode = 0;
        uint8_t _wpm = 20;

        Preferences _config;
};

void vEncoderCheck(void *pvParameters);

#endif  // _KEYER_CONFIG_
