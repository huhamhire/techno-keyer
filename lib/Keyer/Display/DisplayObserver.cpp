#include <Display/DisplayObserver.h>

namespace KeyboardKeyer {
    /**
     * Initialize Observer
     * @param ctx - Display Context
     * @param vfd - VFD Display
     */
    DisplayObserver::DisplayObserver(DisplayContext *ctx, VFD_1605N *vfd) {
        _ctx = ctx;
        _vfd = vfd;
    }

    /**
     * Sync brightness config to VFD
     */
    void DisplayObserver::syncBrightness() {
        if (_bright != _ctx->getBrightness()) {
            _bright = _ctx->getBrightness();
            _vfd->setBrightness(_bright);
        }
    }

    /**
     * Refresh VFD Display
     */
    void DisplayObserver::refreshVFD() {
        for (uint8_t line = 0; line < DISPLAY_LINES; line++) {
            _vfd->displayLine(
                    line, _ctx->getDisplayLine(line)
            );
        }
    }


    /**
     * Task to refresh VFD Display.
     * @param pvParameters
     */
    void vRefreshDisplay(void *pvParameters) {
        DisplayObserver *observer;
        observer = (DisplayObserver *) pvParameters;

        for (;;) {
//            observer->syncBrightness();
            observer->refreshVFD();
            // wait 40ms (25FPS)
            vTaskDelay(40 / portTICK_PERIOD_MS);
        }
    }
}
