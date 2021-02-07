#include "cpu.hpp"

#include <imxrt1062/utility.hpp>
#include "clocks.hpp"
namespace imxdrivers
{

    template <std::uint32_t sys_clock, std::uint32_t resolution>
    class core_timer_t : public imxutility::timer_t<std::uint32_t>
    {
        constexpr auto div = sys_clock / resolution;

    public:
        core_timer_t()
        {
            core_debug_enable();
        }

        virtual std::uint32_t time_elapsed() noexcept override
        {
            return core_cycles() / div;
        }
    };

    /**
     * @brief Enables cortex m7 core debug
     * 
     */
    void core_debug_enable() noexcept
    {
        reg_set(CoreDebug->DEMCR, CoreDebug_DEMCR_TRCENA_Msk);
        reg_write(DWT->LAR, 0xC5ACCE55);
        reg_write(DWT->CYCCNT, 0);
        reg_set(DWT->CTRL, DWT_CTRL_CYCCNTENA_Msk);
    }

    /**
     * @brief Sleep for miliseconds based on core cyccles
     * 
     * @param miliseconds 
     */
    void sleep(std::uint32_t miliseconds) noexcept
    {
        static core_timer_t<get_sys_clock(), 1000ul> core_timer;
        core_timer.restart(miliseconds);

        while (not core_timer.expired())
        {
            continue;
        }
    }

} // namespace imxdrivers