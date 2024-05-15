#include <KeyerDisplay.h>

char* _vfdBuffer[VFD_LINES] = {"", "",};

void setVFDLine(uint8_t line, char *str) {
    if (line < VFD_LINES) {
        _vfdBuffer[line] = str;
    }
}

// Task to refresh VFD Display
void vRefreshVFD(void *pvParameters) {
    VFD_1605N *VFD;
    VFD = (VFD_1605N *)pvParameters;

    for ( ;; ) {
        // Refresh VFD
        for (uint8_t line = 0; line < VFD_LINES; line++) {
            for (int i = 0; i < VFD_BUFF_SIZE; i++) {
                if (i < strlen(_vfdBuffer[line])) {
                    (*VFD).displayChar(1 - line, i, _vfdBuffer[line][i]);
                } else {
                    (*VFD).displayChar(1 - line, i, ' ');
                }
            }
        }

        // wait 40ms
        vTaskDelay(40 / portTICK_PERIOD_MS);
    }
}