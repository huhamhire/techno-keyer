#include <Keyer.h>

char _inputBuffer[32] = "";
char _sendingBuffer[128] = "";

VFD_1605N VFD;
KeyerBuffer buffer;

void CWKeyer::begin() {
    VFD.init();

    xTaskCreate(vRefreshVFD, "vRefreshVFD", 2048, &VFD, 1, NULL);
    char msg[] = "    CW KEYER    ";
    setVFDLine(0, msg);

    delay(1000);
    initKeyerInput(&buffer);

    setVFDLine(0, buffer.getSending());
    setVFDLine(1, buffer.getInput());

    beginCWOutput(&buffer);
    setCWSpeed(20);

    xTaskCreate(vGetKey, "vGetKey", 2048, NULL, 1, NULL);
    xTaskCreate(vSendMorse, "vSendMorse", 2048, NULL, 1, NULL);
}
