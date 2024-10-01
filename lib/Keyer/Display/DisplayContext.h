#ifndef DISPLAY_CONTEXT_H
#define DISPLAY_CONTEXT_H

#include <Arduino.h>

namespace TechnoKeyer {

    #define DISPLAY_LINES   2
    #define DISPLAY_MODES   3
    #define DISPLAY_LINE_SIZE 16

    class DisplayContext {
    public:
        uint8_t getMode();
        void setMode(uint8_t mode);
        void setBrightness(uint16_t value);
        uint16_t getBrightness() const;

        void setTitleLine(char* title);
        void setValueLine(char* value);

        void setTransmitLines(char* tx, char* input);
        void setReceiveLines(char* rx, char* decode);

        char* getDisplayLine(uint8_t lineNum);

    private:
        char* _getInputLine();

        char* _titleBuf = (char *) "";
        char* _valueBuf = (char *) "";

        char* _txBuf = (char *) "";
        char* _inputBuf = (char *) "";
        char _inputLine[DISPLAY_LINE_SIZE] = {0};

        char* _rxBuf = (char *) "";
        char* _decodeBuf = (char *) "";

        uint8_t _mode = 0;
        uint16_t _bright = 500;
    };
}

#endif  // DISPLAY_CONTEXT_H
