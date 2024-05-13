#ifndef _KEYER_MORSE_
#define _KEYER_MORSE_

#include <Arduino.h>

#define LED_PIN 48
#define CW_PIN 42

struct t_mtab {
  char c, pat;
};

void beginCWOutput();
void setCWSpeed(int s);
void SetCWString(char *s);
void appendCWString(char *s);

void vSendMorse(void *pvParameters);


void updateCWSpeed();
void sendDit();
void SendDash();
void sendChar(char c);

#endif  // _KEYER_MORSE_