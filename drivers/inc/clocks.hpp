#ifndef IMXRT_DRIVERS_CLOCKS_HPP_
#define IMXRT_DRIVERS_CLOCKS_HPP_

#include <hardware.hpp>

#include "clock_handler.hpp"

namespace imxdrivers
{
    void enable_clock(const clock_hw_t clock);
    constexpr std::uint32_t get_uart_clock();

} // namespace imxdrivers

#endif //  IMXRT_DRIVERS_CLOCKS_HPP_