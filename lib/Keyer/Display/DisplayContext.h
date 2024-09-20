#ifndef _KEYER_DISPLAY_CONTEXT_
#define _KEYER_DISPLAY_CONTEXT_

#include <Arduino.h>

namespace TechnoKeyer {

    #define DISPLAY_LINES   2
    #define DISPLAY_MODES   3

    class DisplayContext {
    public:
        void setMode(uint8_t mode);
        void setBrightness(uint16_t value);
        uint16_t getBrightness();

        void setTitleLine(char* title);
        void setValueLine(char* value);

        void setTransmitLines(char* tx, char* input);
        void setReceiveLines(char* rx, char* decode);

        char* getDisplayLine(uint8_t lineNum);

    private:
        char* _titleBuf = (char *) "";
        char* _valueBuf = (char *) "";

        char* _txBuf = (char *) "";
        char* _inputBuf = (char *) "";

        char* _rxBuf = (char *) "";
        char* _decodeBuf = (char *) "";

        uint8_t _mode = 0;
        uint16_t _bright = 500;
    };
}

#endif  // _KEYER_DISPLAY_CONTEXT_
