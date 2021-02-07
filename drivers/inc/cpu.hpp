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
        return reg_get(DWT->CYCCNT);
    }

    /**
     * @brief Enables cortex m7 core debug
     * 
     */
    void core_debug_enable() noexcept;

    /**
     * @brief Sleep for miliseconds based on core cyccles
     * 
     * @param miliseconds 
     */
    void sleep(std::uint32_t miliseconds) noexcept;

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_CPU_HPP_