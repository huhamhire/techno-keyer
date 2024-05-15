#include <Keyer.h>

char _inputBuffer[32] = "";
char _sendingBuffer[128] = "";

VFD_1605N VFD;

void CWKeyer::begin() {
    VFD.init();

    xTaskCreate(vRefreshVFD, "vRefreshVFD", 2048, &VFD, 1, NULL);
    char msg[] = "    CW KEYER    ";
    setVFDLine(0, msg);

    delay(1000);
    initKeyerInput(_inputBuffer, _sendingBuffer);

    setVFDLine(0, _sendingBuffer);
    setVFDLine(1, _inputBuffer);

    beginCWOutput();
    setCWSpeed(20);
    setCWString(_sendingBuffer);

    xTaskCreate(vGetKey, "vGetKey", 2048, NULL, 1, NULL);
    xTaskCreate(vSendMorse, "vSendMorse", 2048, NULL, 1, NULL);
}
