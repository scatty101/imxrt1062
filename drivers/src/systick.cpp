#include "systick.hpp"

#include <hardware.hpp>
#include <reg.hpp>

namespace imxdrivers
{
    systick_t::systick_t(const std::uint32_t &ticks) noexcept
    {
        SysTick_Config(ticks);
    }

    inline void systick_t::handler() noexcept
    {
        tick_++;
    }
    inline std::uint32_t systick_t::time() const noexcept
    {
        return tick_;
    }

} // namespace imxdrivers
