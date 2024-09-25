#include "SignalEventsBuffer.h"

namespace TechnoKeyer {
    /**
     * Append event time
     * @param duration
     */
    void SignalEventsBuffer::appendEventTime(uint16_t duration) {
        _events[_nextIdx] = duration;
        _nextIdx = (_nextIdx + 1) % MORSE_EVENTS_SIZE;
    }

    /**
     * Get average time of events
     * @return
     */
    uint16_t SignalEventsBuffer::getAverageTime() {
        uint8_t count = 0;
        uint32_t sum = 0;
        for (uint16_t _eventTime : _events) {
            if (_eventTime != 0) {
                sum += _eventTime;
                count++;
            }
        }
        return count == 0 ? 0 : sum / count;
    }

    /**
     * Clear buffer
     */
    void SignalEventsBuffer::clear() {
        memset(_events, 0, 2 * MORSE_EVENTS_SIZE);
    }

} // TechnoKeyer