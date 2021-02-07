#include <init.hpp>

#include <imxrt1062/hardware.hpp>

#include <pin_mux.h>
#include <board.h>
#include <clock_config.h>

namespace imxdrivers
{
    /**
     * @brief SDK based init for hardware
     * 
     * If we wants to perform some perihperal configurations, such as enabling UART, finding clock dividers etc, we need to:
     * 1. Enable clocks for perihperal - this will be handled by ctor
     * 2. Have clocks already configured to predefined value (in nxp its in defines in clock_config.h) 
     * 
     * So, we call imxdrivers::init() in start up code - ResetISR, just before c++ initizalization.
     * Then, every c++ peripheral driver have to firstly enable proper clock to access peripherals without error.
     * 
     */
    void init()
    {
        BOARD_InitBootPins();
        BOARD_InitBootClocks();
        BOARD_ConfigMPU();
    }
} // namespace imxdrivers