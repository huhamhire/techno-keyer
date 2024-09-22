#include "MorseCodec.h"

namespace TechnoKeyer {
    MorseCodec::MorseCodec() {
        uint8_t morseCount = (sizeof (morseTable) / sizeof (morseTable[0]));

        for (uint8_t i = 0; i < morseCount; i++) {
            _charToCode.insert(std::make_pair(
                    morseTable[i].character,
                    morseTable[i].code));
            _codeToChar.insert(std::make_pair(
                    morseTable[i].code,
                    morseTable[i].character));
        }
    }

    /**
     * Get character from a Morse code
     * @param code
     * @return
     */
    char MorseCodec::getChar(uint8_t code) {
        auto c = _codeToChar.find(code);
        if (c != _codeToChar.end()) {
            return c->second;
        } else {
            // Not found, use ~
            return '~';
        }
    }

    /**
     * Get Morse code for a character
     * @param c
     * @return
     */
    uint8_t MorseCodec::getCode(char c) {
        auto code = _charToCode.find(c);
        if (code != _charToCode.end()) {
            return code->second;
        } else {
            // Not found, use 0b1
            return 0b1;
        }
    }
} // TechnoKeyer