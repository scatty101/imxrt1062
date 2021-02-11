#ifndef IMXRT_DRIVERS_CLOCK_HANDLER_HPP_
#define IMXRT_DRIVERS_CLOCK_HANDLER_HPP_

#include <drivers/fsl_clock.h>

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
    struct spec_t
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

    /**
     * @brief Default specification for finding proper clock
     * 
     * @tparam T 
     */
    template <typename T>
    class default_spec_t : public spec_t<T>
    {
        const T &elem_;

    public:
        default_spec_t(const T &_elem) noexcept : elem_(_elem)
        {
        }

        virtual bool is_satisfied(const T &item) const override
        {
            return elem_ == item;
        }
    };

    /**
     * @brief Simple clock finder, based on initializer list
     * 
     * Initializer list was choosen, because of manufacturer header files - they keep clocks just like initializer list
     * 
     */
    struct clock_t
    {
        /**
         * @brief Default list type 
         * 
         * @tparam T peripheral base ptr type
         */
        template <typename T>
        using list_t = std::initializer_list<T>;

        /**
         * @brief Clock finder based on initializer list
         * 
         * Clock position and peripheral position in list have to match.
         * 
         * @tparam peripheral_t peripheral base ptr type
         * @param clocks        clocks list
         * @param peripherals   peripherals list
         * @param spec 
         * @return std::optional<clock_hw_t> nullopt, if proper clock wasn't find, otherwise clock_hw_t
         */
        template <typename peripheral_t>
        static std::optional<clock_hw_t> get_clock(const list_t<clock_hw_t> &clocks, const list_t<peripheral_t> &peripherals, const spec_t<peripheral_t> &spec)
        {
            auto satisfied = [&](const peripheral_t &elem) {
                return spec.is_satisfied(elem);
            };

            auto iterator = std::find_if(peripherals.begin(), peripherals.end(), satisfied);
            if (iterator == peripherals.end())
            {
                return std::nullopt;
            }

            auto pos = std::distance(peripherals.begin(), iterator);

            return *(clocks.begin() + pos);
        }
    };
} // namespace imxdrivers

#endif // IMXRT_DRIVERS_CLOCK_HANDLER_HPP_