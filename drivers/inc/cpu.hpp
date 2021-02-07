#ifndef IMXRT_DRIVERS_CPU_HPP_
#define IMXRT_DRIVERS_CPU_HPP_

#include <imxrt1062/hardware.hpp>
#include <reg.hpp>

#include <cstdint>

namespace imxdrivers
{
    /**
     * @brief NOP operation
     * 
     * @param times 
     */
    static inline void nop(std::uint32_t times = 1) noexcept
    {
        while (times--)
        {
            asm volatile("nop");
        }
    }

    /**
     * @brief Returns core cycles from start, if core debug is enabled
     * 
     * @return std::uint32_t 
     */
    static inline std::uint32_t core_cycles() noexcept
    {
        return reg_read(DWT->CYCCNT);
    }

    /**
     * @brief Enables cortex m7 core debug
     * 
     */
    static inline void core_debug_enable() noexcept
    {
        reg_set(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
        reg_write(DWT->LAR, 0xC5ACCE55);
        reg_write(DWT->CYCCNT, 0);
        reg_set(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
    }

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_CPU_HPP_