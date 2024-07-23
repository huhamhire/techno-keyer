#ifndef _KEYER_DISPLAY_
#define _KEYER_DISPLAY_

#include <Arduino.h>
#include <VFD_1605N.h>

#define VFD_BUFF_SIZE 16
#define VFD_LINES 2

class KeyerDisplay {
    public:
        KeyerDisplay(VFD_1605N* VFD);
        void setVFDLine(uint8_t line, char *str);
        void setBrightness(uint16_t brightness);
        uint16_t getBrightness();
        void refreshVFD();

    private:
        VFD_1605N* _VFD;
        char* _buffer[VFD_LINES] = {(char*) "", (char*) ""};
        uint16_t _brightness = 500;
};

void vRefreshVFD(void *pvParameters);

#endif  // _KEYER_DISPLAY_
