#include <Keyer.h>

char *_inputBuffer = "";
char *sendingStr = "";

VFD_1605N VFD;

void CWKeyer::begin() {
    VFD.init();
    beginCWOutput();
    
    KeyerInputInit(_inputBuffer);

    xTaskCreate(vGetKey, "vGetKey", 2048, NULL, 1, NULL);
    xTaskCreate(vRefreshVFD, "vRefreshVFD", 1024, &VFD, 1, NULL);
    xTaskCreate(vSendMorse, "vSendMorse", 1024, NULL, 1, NULL);

    char *msg = "  WELCOME  ";
    setVFDLine(0, msg);
    setVFDLine(1, _inputBuffer);
}
