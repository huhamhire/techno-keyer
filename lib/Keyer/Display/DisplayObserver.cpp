#include <Display/DisplayObserver.h>

namespace TechnoKeyer {
    VFD_1605N *DisplayObserver::_vfd = new VFD_1605N();

    /**
     * Initialize Observer
     * @param ctx - Display Context
     */
    DisplayObserver::DisplayObserver(DisplayContext *ctx) {
        _ctx = ctx;
        static SPIBus spi;
        _vfd->begin(spi.getSPI(),
                    VFD_EN_PIN,
                    VFD_RST_PIN,
                    VFD_CS_PIN);
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
            observer->refreshVFD();
            // wait 40ms (25FPS)
            vTaskDelay(40 / portTICK_PERIOD_MS);
        }
    }
}
