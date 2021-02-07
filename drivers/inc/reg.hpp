#ifndef IMXRT_DRIVERS_REG_HPP_
#define IMXRT_DRIVERS_REG_HPP_

#include <imxrt1062/hardware.hpp>

namespace imxdrivers
{
    /**
     * @brief DSB
     * 
     */
    static inline void data_sync()
    {
        __DSB();
    }

    /**
     * @brief Sometimes IRQ are executed so fast, that irq flag isn't cleared until leave of irq. This function solves this problem.
     * 
     */
    static inline void irq_save_exit()
    {
        data_sync();
    }
    /**
     * @brief Performs OR operation.
     * 
     * @tparam reg_t     
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_set(reg_t &reg, const value_t &value = static_cast<value_t>(0))
    {
        reg |= static_cast<reg_t>(value);
    }
    /**
     * @brief Performs write operation.
     * 
     * @tparam reg_t 
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_write(reg_t &reg, const value_t &value = static_cast<value_t>(0))
    {
        reg = static_cast<reg_t>(value);
    }

    /**
     * @brief Peforms AND NOT operation
     * 
     * @tparam reg_t 
     * @tparam value_t 
     * @param reg 
     * @param value 
     */
    template <typename reg_t, typename value_t>
    static inline constexpr void reg_clear(reg_t &reg, const value_t &value = static_cast<value_t>(0))
    {
        reg &= static_cast<reg_t>(~value);
    }

    /**
     * @brief Performs read operation
     * 
     * @tparam reg_t 
     * @param reg 
     * @return constexpr reg_t 
     */
    template <typename reg_t>
    static inline constexpr reg_t reg_get(const reg_t &reg)
    {
        return reg;
    }

    template <typename reg_t, typename mask_t, typename shift_t, typename value_t>
    static inline constexpr void reg_manipulate_mask(reg_t &reg, const mask_t &mask, const shift_t &shift, const value_t &value)
    {
        reg_clear(reg, mask);
        reg_set(reg, (value << shift) & mask);
    }

    template <typename reg_t, typename bit_pos_t>
    static inline bool reg_get_bit(const reg_t &reg, const bit_pos_t &bit_pos)
    {
        return (reg_get(reg) >> bit_pos) & 0x1;
    }

    template <typename reg_t, typename bit_pos_t>
    static inline constexpr void reg_clear_bit(reg_t &reg, const bit_pos_t &bit_pos)
    {
        reg_clear(reg, 1 << bit_pos);
    }

    template <typename reg_t, typename bit_pos_t>
    static inline constexpr void reg_set_bit(reg_t &reg, const bit_pos_t &bit_pos)
    {
        reg_set(reg, 1 << bit_pos);
    }

    template <typename reg_t, typename bit_pos_t>
    static inline constexpr void reg_manipulate_bit(reg_t &reg, const bit_pos_t &bit_pos, const bool &value)
    {
        if (value)
        {
            reg_set_bit(reg, bit_pos);
        }
        else
        {
            reg_clear_bit(reg, bit_pos);
        }
    }

} // namespace imxdrivers

#endif //  IMXRT_DRIVERS_REG_HPP_