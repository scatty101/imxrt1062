#include "clocks.hpp"

#include <cstdint>

#include <drivers/fsl_clock.h>

namespace imxdrivers
{
    /**
     * @brief Enables clock via SDK driver
     * 
     * @param clock 
     */
    void enable_clock(const clock_hw_t clock)
    {
        CLOCK_EnableClock(clock);
    }


} // namespace imxdrivers