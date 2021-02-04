#include <init.hpp>

#include <hardware.hpp>

#include <pin_mux.h>
#include <board.h>
#include <clock_config.h>

namespace imxdrivers
{
    void init()
    {
        BOARD_InitBootPins();
        BOARD_InitBootClocks();
        BOARD_ConfigMPU();
    }
} // namespace imxdrivers