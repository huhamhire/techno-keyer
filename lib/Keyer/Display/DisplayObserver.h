#ifndef DISPLAY_OBSERVER_H
#define DISPLAY_OBSERVER_H

#include <VFD_1605N.h>

#include <IO/SPIBus.h>
#include <Display/DisplayContext.h>

namespace TechnoKeyer {

    class DisplayObserver {
    public:
        explicit DisplayObserver(DisplayContext* ctx);
        void syncBrightness();
        void refreshVFD();

    private:
        uint16_t _bright;

        DisplayContext* _ctx;

        static VFD_1605N* _vfd;
    };

    [[noreturn]] void vRefreshDisplay(void *pvParameters);
} // TechnoKeyer

#endif // DISPLAY_OBSERVER_H
