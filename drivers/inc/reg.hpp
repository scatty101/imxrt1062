#if !defined IMXRT_DRIVERS_REG_HPP_
#define IMXRT_DRIVERS_REG_HPP_

#include <hardware.hpp>

namespace imxdrivers
{
    /**
     * @brief Sometimes IRQ are executed so fast, that irq flag isn't cleared until leave of irq. This function solves this problem
     * 
     */
    static inline void irq_save_exit()
    {
        __DSB();
    }

    /**
     * @brief Access to volatile registers. Performs OR operation.
     * 
     * @tparam reg_t     
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_set(reg_t *reg, const value_t &value = static_cast<value_t>(0))
    {
        *reinterpret_cast<volatile reg_t *>(reg) |= static_cast<reg_t>(value);
    }
    /**
     * @brief Access to volatile registers. Performs write operation.
     * 
     * @tparam reg_t 
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_write(reg_t *reg, const value_t &value = static_cast<value_t>(0))
    {
        *reinterpret_cast<volatile reg_t *>(reg) = static_cast<reg_t>(value);
    }

    /**
     * @brief Access to volatile registers. Peforms AND NOT operation
     * 
     * @tparam reg_t 
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_clear(reg_t *reg, const value_t &value = static_cast<value_t>(0))
    {
        *reinterpret_cast<volatile reg_t *>(reg) &= static_cast<reg_t>(~value);
    }

    /**
     * @brief Access to volatile registers. Performs read operation
     * 
     * @tparam reg_t 
     * @param reg 
     * @return constexpr reg_t 
     */
    template <typename reg_t>
    static inline constexpr reg_t reg_read(reg_t *reg)
    {
        return (*reinterpret_cast<volatile reg_t *>(reg));
    }

} // namespace imxdrivers

#endif //  IMXRT_DRIVERS_REG_HPP_