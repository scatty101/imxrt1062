#if !defined IMXRT_SYSTICK_HPP_
#define IMXRT_SYSTICK_HPP_

#include <cstdint>

namespace imxdrivers
{
    class systick_t
    {
        std::uint32_t tick_{0};

    public:
        systick_t(const systick_t &) = delete;
        systick_t &operator=(const systick_t &) = delete;

        systick_t(const std::uint32_t &ticks) noexcept;
        ~systick_t() = default;

        inline std::uint32_t time() const noexcept;
        inline void handler() noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_SYSTICK_HPP_