#ifndef IMXRT_DRIVERS_CLOCKS_HPP_
#define IMXRT_DRIVERS_CLOCKS_HPP_

#include <imxrt1062/hardware.hpp>
#include <board/clock_config.h>

#include "clock_handler.hpp"
namespace imxdrivers
{
    void enable_clock(const clock_hw_t clock);

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
     * @brief Returns predefined value for cpu clockk
     * 
     * @return constexpr std::uint32_t 
     */
    constexpr std::uint32_t get_sys_clock()
    {
        return BOARD_BOOTCLOCKRUN_AHB_CLK_ROOT;
    }
} // namespace imxdrivers

#endif //  IMXRT_DRIVERS_CLOCKS_HPP_