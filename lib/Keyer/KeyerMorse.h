#ifndef _KEYER_MORSE_
#define _KEYER_MORSE_

#include <Arduino.h>

#include <KeyerBuffer.h>

#define CW_PIN 14

#define BZ_PIN 2
// CW Pitch
#define BZ_FREQ 750
#define BZ_CHANNEL 0
#define BZ_RESOLUTION 8

struct t_mtab {
  char c, pat;
};

const struct t_mtab morsetab[] = {
    {'.', 106},
    {',', 115},
    {'?', 76},
    {'/', 41},
    {'A', 6},
    {'B', 17},
    {'C', 21},
    {'D', 9},
    {'E', 2},
    {'F', 20},
    {'G', 11},
    {'H', 16},
    {'I', 4},
    {'J', 30},
    {'K', 13},
    {'L', 18},
    {'M', 7},
    {'N', 5},
    {'O', 15},
    {'P', 22},
    {'Q', 27},
    {'R', 10},
    {'S', 8},
    {'T', 3},
    {'U', 12},
    {'V', 24},
    {'W', 14},
    {'X', 25},
    {'Y', 29},
    {'Z', 19},
    {'1', 62},
    {'2', 60},
    {'3', 56},
    {'4', 48},
    {'5', 32},
    {'6', 33},
    {'7', 35},
    {'8', 39},
    {'9', 47},
    {'0', 63}
};

#define N_MORSE (sizeof(morsetab)/sizeof(morsetab[0]))

class KeyerMorse {
    public:
        KeyerMorse(KeyerBuffer* buffer);
        void begin();

        void setSpeed(uint8_t s);
        uint8_t getSpeed();
        void sendChar(char c);
        void sendBuffer();

    protected:
        void _sendDit();
        void _sendDah();
        void _updateSpeed();

    private:
        uint16_t _dot_len;
        uint16_t _dash_len;
        uint8_t _speed;

        KeyerBuffer* _buffer;
};

void vSendMorse(void *pvParameters);

#endif  // _KEYER_MORSE_