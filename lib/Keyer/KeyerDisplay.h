#ifndef _KEYER_DISPLAY_
#define _KEYER_DISPLAY_

#include <Arduino.h>
#include <VFD_1605N.h>

#define VFD_BUFF_SIZE 16
#define VFD_LINES 2

void setVFDLine(uint8_t line, char *str);
void vRefreshVFD(void *pvParameters);

#endif  // _KEYER_DISPLAY_
