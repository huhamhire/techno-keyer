#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>
#include <Control/TunerControl.h>

namespace TechnoKeyer {

    class Receiver {
    public:
        void begin();
    private:
        static TunerControl *_tuner;
    };

} // TechnoKeyer

#endif // RECEIVER_H
