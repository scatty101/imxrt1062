#include "clocks.hpp"

#include <cstdint>

#include <board/clock_config.h>
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

    /**
     * @brief Returns predefined value for uart clock
     * 
     * @return constexpr std::uint32_t 
     */
    constexpr std::uint32_t get_uart_clock()
    {
        return BOARD_BOOTCLOCKRUN_UART_CLK_ROOT;
    }

    /**
     * @brief Get the cpu clock value
     * 
     * @return constexpr std::uint32_t 
     */
    constexpr std::uint32_t get_sys_clock()
    {
        return BOARD_BOOTCLOCKRUN_AHB_CLK_ROOT;
    }

} // namespace imxdrivers