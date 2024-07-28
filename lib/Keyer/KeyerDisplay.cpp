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

// Set VFD Display Brightness
void KeyerDisplay::setBrightness(uint16_t brightness) {
    _brightness = brightness;
    (*_VFD).setBrightness(brightness);
}

// Get VFD Display Brightness
uint16_t KeyerDisplay::getBrightness() {
    return _brightness;
}

// Refresh VFD Display
void KeyerDisplay::refreshVFD() {
    for (uint8_t line = 0; line < VFD_LINES; line++) {
        (*_VFD).displayLine(line, _buffer[line]);
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
