#include <Arduino.h>
#include <VFD_1605N.h>
#include <CH9350_USBKEY.h>
#include <Keyer.h>

CWKeyer keyer;

void setup() {
    Serial.begin(115200);
    Serial.println("Keyboard CW Keyer");

    keyer.begin();
}


void loop() {
    ;
}
