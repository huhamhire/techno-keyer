#include <Display/DisplayObserver.h>

namespace KeyboardKeyer {
    VFD_1605N *DisplayObserver::_vfd = new VFD_1605N();

    /**
     * Initialize Observer
     * @param ctx - Display Context
     */
    DisplayObserver::DisplayObserver(DisplayContext *ctx) {
        _ctx = ctx;
        SPIBus spi;
        _vfd->init(spi.getSPI());
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
