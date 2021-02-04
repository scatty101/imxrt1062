#if !defined IMXRT1062_DRIVERS_CLOCKS_HPP_
#define IMXRT1062_DRIVERS_CLOCKS_HPP_

#include <hardware.hpp>
#include <fsl_clock.h>

#include <initializer_list>
#include <optional>

namespace imxdrivers
{
    // Implementation of clock enabling via hardware type
    using clock_hw_t = clock_ip_name_t; /*!< Type used by SDK*/

    /**
     * @brief Specification to find proper clock
     * 
     * @tparam T usually it will be some kind of peripheral type, like GPT_Type *, LPUART_Type * etc.
     */
    template <typename T>
    struct specification
    {
        /**
         * @brief Method to compare next peripherals
         * 
         * @param item      item to compare
         * @return true     if its right peripheral
         * @return false    otherwise
         */
        virtual bool is_satisfied(const T &item) const = 0;
    };

    template <typename T>
    class default_specification : public specification<T>
    {
        const T &elem_;

    public:
        default_specification(const T &_elem) noexcept : elem_(_elem)
        {
        }

        virtual bool is_satisfied(const T &item) const override
        {
            return elem_ == item;
        }
    };

    template <typename peripheral_t>
    class clock_t
    {
        template <typename T>
        using list_t = std::initializer_list<T>;

        const list_t<clock_hw_t> &clocks_;
        const list_t<peripheral_t> &peripherals_;

    public:
        clock_t(const list_t<clock_ip_name_t> &_clocks, const list_t<peripheral_t> &_peripherals) noexcept : clocks_(_clocks), peripherals_(_peripherals)
        {
        }

        std::optional<clock_hw_t> get_clock(const specification<peripheral_t> &spec) noexcept
        {
            auto satisfied = [&](const peripheral_t &elem) {
                return spec.is_satisfied(elem);
            };

            auto iterator = std::find_if(peripherals_.begin(), peripherals_.end(), satisfied);
            if (iterator >= peripherals_.end())
            {
                return std::nullopt;
            }

            auto pos = std::distance(peripherals_.begin(), iterator);

            return *(clocks_.begin() + pos);
        }
    };

} // namespace imxdrivers

#endif //  IMXRT1062_DRIVERS_CLOCKS_HPP_