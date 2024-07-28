#include <Arduino.h>
#include <VFD_1605N.h>
#include <CH9350_USBKEY.h>
#include <Keyer.h>

Keyer keyer;

void setup() {
    Serial.begin(115200);
    Serial.println("Keyboard CW Keyer");
    setCpuFrequencyMhz(80);

    keyer.begin();
}


void loop() {
    ;
}
