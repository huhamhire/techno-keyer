#include "Receiver.h"

namespace TechnoKeyer {
    TunerControl *Receiver::_tuner = new TunerControl();

    void Receiver::begin() {
        _tuner->begin();
    }
} // TechnoKeyer