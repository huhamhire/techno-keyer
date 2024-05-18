#include <KeyerDisplay.h>

// VFD Display constructor
KeyerDisplay::KeyerDisplay(VFD_1605N* VFD) {
    _VFD = VFD;
}

// Set VFD Display Line
void KeyerDisplay::setVFDLine(uint8_t line, char *str) {
    if (line < VFD_LINES) {
        _buffer[line] = str;
    }
}

// Refresh VFD Display
void KeyerDisplay::refreshVFD() {
    for (uint8_t line = 0; line < VFD_LINES; line++) {
        for (int i = 0; i < VFD_BUFF_SIZE; i++) {
            if (i < strlen(_buffer[line])) {
                (*_VFD).displayChar(1 - line, i, _buffer[line][i]);
            } else {
                (*_VFD).displayChar(1 - line, i, ' ');
            }
        }
    }
}

// Task to refresh VFD Display
void vRefreshVFD(void *pvParameters) {
    KeyerDisplay *display;
    display = (KeyerDisplay *)pvParameters;

    for ( ;; ) {
        display->refreshVFD();
        // wait 40ms
        vTaskDelay(40 / portTICK_PERIOD_MS);
    }
}
