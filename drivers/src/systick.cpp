#include "systick.hpp"

#include <hardware.hpp>
#include <reg.hpp>

namespace imxdrivers
{
    systick_t::systick_t(const std::uint32_t &ticks, const bool &enable) noexcept
    {
        config(ticks, enable);
    }

    systick_t::systick_t() noexcept
    {
    }

    void systick_t::config(const std::uint32_t &ticks, const bool &enable) const noexcept
    {
        SysTick_Config(ticks);
        this->enable(enable);
    }

    inline void systick_t::enable(const bool &enable) const noexcept
    {
        if (enable)
        {
            reg_set(&SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
        }
        else
        {
            reg_clear(&SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
        }
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
