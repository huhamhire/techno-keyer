#ifndef SIGNAL_EVENTS_BUFFER_H
#define SIGNAL_EVENTS_BUFFER_H

#include <Arduino.h>

namespace TechnoKeyer {
    #define MORSE_EVENTS_SIZE 16

    class SignalEventsBuffer {
    public:
        SignalEventsBuffer();
        void appendEventTime(uint16_t duration);
        uint16_t getAverageTime();
        void clear();

    private:
        uint16_t _events[MORSE_EVENTS_SIZE]{};
        uint8_t _nextIdx = 0;
    };

} // TechnoKeyer

#endif // SIGNAL_EVENTS_BUFFER_H
