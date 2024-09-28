#ifndef KEYER_MODES_H
#define KEYER_MODES_H

namespace TechnoKeyer {
    #define MODE_LOCK_MS    3000

    enum KeyerMode {
        CONFIG_MODE = 0,
        TX_MODE = 1,
        RX_MODE = 2,
    };

    typedef std::function<bool(KeyerMode mode)> onCheckMode;

    class ModeMutexComponent {
    public:
        /**
         * Check component is busy
         * @return
         */
        virtual bool isBusy() const {
            unsigned long now = millis();
            if (now - _lastEventTime > MODE_LOCK_MS) {
                return true;
            }
            return false;
        };

        /**
         * Keep component busy
         */
        void keepBusy() {
            _lastEventTime = millis();
        }

        /**
         * Activate component
         */
        virtual void activate() {
            _active = true;
        };

        /**
         * Deactivate component
         */
        virtual void deactivate() {
            _active = false;
        };

    protected:
        bool _active = false;
        unsigned long _lastEventTime = 0;
    };
}

#endif // KEYER_MODES_H
