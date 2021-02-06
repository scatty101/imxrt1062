#if !defined IMXRT_UTILITY_HPP_
#define IMXRT_UTILITY_HPP_

#include <cstdint>
#include <limits>
#include <functional>
namespace imxutility
{
    /**
     * @brief Unsigned type software timer.
     * 
     * Need only to override time_elapsed
     * 
     * @tparam T system tick value type 
     */
    template <typename T>
    class timer_t
    {
        T tick_;                                                                                                               /*!< Current tick to detect expiration */
        bool running_;                                                                                                         /*!< Current timer state */
        constexpr static T TIMER_MASK = static_cast<T>((UINTMAX_C(1) << (std::numeric_limits<T>::digits - 1)) - UINTMAX_C(1)); /*!< Mask used to detect expire*/

    public:
        static_assert(std::numeric_limits<T>::is_signed == false,
                      "the T must be unsigned");

        /**
         * @brief Construct a new timer t object
         * 
         */
        timer_t() noexcept : tick_(static_cast<T>(0)), running_(false){};

        /**
         * @brief Destroy the timer t object
         * 
         */
        virtual ~timer_t() = default;

        /**
         * @brief Functio, to be overriden with current system time (time since start)
         * 
         * 
         * 
         * @return T 
         */
        virtual T time_elapsed() noexcept = 0;

        /**
         * @brief Returns timer state
         * 
         * @return true   if timer is running
         * @return false  otheriwse
         */
        inline bool running() const noexcept
        {
            return running_;
        }

        /**
         * @brief Checks, whether timer expired
         * 
         * Expired is triggered only once after restart. Every next expired() call without restart will return false
         * 
         * @return true     if timer is running and expired
         * @return false    otherwise
         */
        inline bool expired() noexcept
        {
            if (running() and timeout())
            {
                running_ = false;
                return true;
            }
            return false;
        }
        /**
         * @brief Stops timer
         * 
         */
        inline void stop() noexcept
        {
            running_ = false;
        }

        /**
         * @brief Restarts timer with new value
         * 
         * Timer can always be restarted, even if already running
         * 
         * @param time 
         */
        inline void restart(const T &time) noexcept
        {
            running_ = true;
            tick_ = time_elapsed() + time;
        }

    private:
        /**
         * @brief Checks, whether timeout is detected
         * 
         * @return true     for timeout
         * @return false    otherwise
         */
        inline bool timeout() noexcept
        {
            const T DELTA = time_elapsed() - tick_;
            return DELTA <= TIMER_MASK;
        }
    };

} // namespace imxutility

#endif // IMXRT_UTILITY_HPP_