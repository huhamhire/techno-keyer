#ifndef _KEYER_INPUT_
#define _KEYER_INPUT_

#include <Arduino.h>
#include <CH9350_USBKEY.h>

#define SERIAL_RX_PIN 15
#define SERIAL_TX_PIN 16

#define DEBOUNCE_TIME 100
#define INPUT_BUFFER_SIZE 32

void initKeyerInput(char* input, char* sending);
void vGetKey(void *pvParameters);

#endif  // _KEYER_INPUT_
