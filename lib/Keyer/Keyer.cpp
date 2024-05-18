#include <Keyer.h>


void CWKeyer::begin() {
    static VFD_1605N VFD;
    VFD.init();

    static KeyerDisplay display(&VFD);
    xTaskCreate(vRefreshVFD, "vRefreshVFD", 2048, &display, 1, NULL);
    char msg[] = "    CW KEYER    ";
    display.setVFDLine(0, msg);

    delay(2000);

    static KeyerBuffer buffer;
    static KeyerInput input(&buffer);
    input.init();

    display.setVFDLine(0, buffer.getSending());
    display.setVFDLine(1, buffer.getInput());
    
    static KeyerMorse morse(&buffer);
    morse.begin();
    morse.setSpeed(20);

    xTaskCreate(vGetKey, "vGetKey", 2048, &input, 1, NULL);
    xTaskCreate(vSendMorse, "vSendMorse", 2048, &morse, 1, NULL);
}
