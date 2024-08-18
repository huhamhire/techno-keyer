#ifndef _KEYER_DISPLAY_OBSERVER_
#define _KEYER_DISPLAY_OBSERVER_

#include <VFD_1605N.h>
#include <Display/DisplayContext.h>

namespace KeyboardKeyer {

    class DisplayObserver {
    public:
        DisplayObserver(DisplayContext* ctx, VFD_1605N* vfd);
        void syncBrightness();
        void refreshVFD();

    private:
        uint16_t _bright;

        DisplayContext* _ctx;
        VFD_1605N* _vfd;
    };

    void vRefreshDisplay(void *pvParameters);
} // KeyboardKeyer

#endif // _KEYER_DISPLAY_OBSERVER_
