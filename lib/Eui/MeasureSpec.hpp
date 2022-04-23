#ifndef _MEASURE_SPEC_H_
#define _MEASURE_SPEC_H_
#include <stdint.h>

#define MEASURE_SPEC_CLASS uint16_t

namespace Measure
{
    enum MeasureMode
    {
        AT_MOST = 0,
        FILL = 1,
        EXACTLY = 2,
        UNSPECIFIED = 3
    };

    static MeasureMode getMode(MEASURE_SPEC_CLASS measureSpec)
    {
        auto mode = (measureSpec & 0xC000) >> 14;
        if (mode == Measure::AT_MOST)
            return Measure::AT_MOST;
        if (mode == Measure::FILL)
            return Measure::FILL;
        if (mode == Measure::EXACTLY)
            return Measure::EXACTLY;
        return Measure::UNSPECIFIED;
    }

    static uint16_t getSize(MEASURE_SPEC_CLASS measureSpec)
    {
        return measureSpec & 0x3FFF;
    }

    static MEASURE_SPEC_CLASS makeMeasureSpec(uint16_t size, MeasureMode mode)
    {

        return (MEASURE_SPEC_CLASS)(getSize(size) | (mode << 14));
    }
}

#endif
