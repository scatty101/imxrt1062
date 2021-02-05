#if !defined IMXRT_UTILITY_HPP_
#define IMXRT_UTILITY_HPP_

#include <cstdint>
#include <limits>
#include <functional>

namespace imxutility
{
    template <typename T>
    class timer_t
    {
        T tick_;
        bool running_;
        constexpr static T TIMER_MASK = static_cast<T>((UINTMAX_C(1) << (std::numeric_limits<T>::digits - 1)) - UINTMAX_C(1));

    public:
        static_assert(std::numeric_limits<T>::is_signed == false,
                      "the T must be unsigned");

        timer_t() noexcept : tick_(static_cast<T>(0)), running_(false){};

        virtual ~timer_t() = default;
        virtual T get_time_elapsed() noexcept = 0;

        inline bool running() const noexcept
        {
            return running_;
        }

        inline bool expired() noexcept
        {
            if (running() and timeout())
            {
                running_ = false;
                return true;
            }
            return false;
        }

        inline void stop() noexcept
        {
            running_ = false;
        }

        inline void restart(const T &time) noexcept
        {
            running_ = true;
            tick_ = get_time_elapsed() + time;
        }

    private:
        inline bool timeout() const noexcept
        {
            const T DELTA = get_time_elapsed() - tick_;
            return DELTA <= TIMER_MASK;
        }
    };

} // namespace imxutility

#endif // IMXRT_UTILITY_HPP_