#ifndef IMXRT_DRIVERS_UART_HARDWARE_HPP_
#define IMXRT_DRIVERS_UART_HARDWARE_HPP_

#include <cstdint>
#include <imxrt1062/hardware.hpp>
#include <imxrt1062/utility.hpp>

#include "reg.hpp"
#include "clocks.hpp"

namespace imxdrivers
{
    using uart_hw_t = LPUART_Type *;

    class uart_clock_spec_t : public default_spec_t<uart_hw_t>
    {
    public:
        using default_spec_t<uart_hw_t>::default_spec_t;
    };

    enum class uart_baud_rate_t
    {
        baud_9600 = 9600ul,
        baud_14400 = 14400ul,
        baud_19200 = 19200ul,
        baud_38400 = 38400ul,
        baud_57600 = 57600ul,
        baud_115200 = 115200ul,
        baud_230400 = 230400ul,
        baud_460800 = 460800ul,
        baud_921600 = 921600ul
    };

    enum class uart_stop_bit_t
    {
        stop_bit_1,
        stop_bit_2,
    };

    enum class uart_parity_t
    {
        even,
        odd,
        none
    };

    enum class uart_data_bits_t
    {
        data_bits_7,
        data_bits_8,
        data_bits_9
    };

    enum class uart_timeout_t
    {
        timeout_1_char = 0b000,
        timeout_2_char = 0b001,
        timeout_4_char = 0b010,
        timeout_8_char = 0b011,
        timeout_16_char = 0b100,
        timeout_32_char = 0b101,
        timeout_64_char = 0b110,
        timeout_128_char = 0b111,
    };

    struct uart_config_t
    {
        uart_baud_rate_t baud;
        uart_stop_bit_t stop_bit;
        uart_parity_t parity;
        uart_data_bits_t data_bits;
        uart_timeout_t timeout;
    };

    class uart_hardware_t
    {
        const uart_hw_t uart_;

    public:
        enum class irq_enable_flags_t
        {
            overrun = LPUART_CTRL_ORIE_SHIFT,
            noise_error = LPUART_CTRL_NEIE_SHIFT,
            framing_error = LPUART_CTRL_FEIE_SHIFT,
            parity_error = LPUART_CTRL_PEIE_SHIFT,
            tx_empty = LPUART_CTRL_TIE_SHIFT,
            tx_complete = LPUART_CTRL_TCIE_SHIFT,
            rx_full = LPUART_CTRL_RIE_SHIFT,
            line_idle = LPUART_CTRL_ILIE_SHIFT,

        };
        enum class irq_status_flags_t
        {
            overrun = LPUART_STAT_OR_SHIFT,
            noise_error = LPUART_STAT_NF_SHIFT,
            framing_error = LPUART_STAT_FE_SHIFT,
            parity_error = LPUART_STAT_PF_SHIFT,
            tx_empty = LPUART_STAT_TDRE_SHIFT,
            tx_complete = LPUART_STAT_TC_SHIFT,
            rx_full = LPUART_STAT_RDRF_SHIFT,
            line_idle = LPUART_STAT_IDLE_SHIFT,
        };

        /**
         * @brief Copy ctor is forbidden
         * 
         */
        uart_hardware_t(const uart_hardware_t &) = delete;
        /**
         * @brief Move ctor is forbidden
         * 
         * @return uart_hardware_t& 
         */
        uart_hardware_t &operator=(const uart_hardware_t &) = delete;

        uart_hardware_t(const uart_hw_t _uart) noexcept;
        ~uart_hardware_t();

        void config(const uart_config_t &cfg) noexcept;
        void enable(const bool &enable) noexcept;
        void debug(const bool &enable) noexcept;

        inline bool tx_empty() noexcept
        {
            return irq_status(irq_status_flags_t::tx_empty);
        }
        inline bool rx_full() noexcept
        {
            return irq_status(irq_status_flags_t::rx_full);
        }

    protected:
        inline std::uint32_t get_data_register() noexcept
        {
            return reg_get(uart_->DATA);
        }
        inline std::uint8_t read_char() noexcept
        {
            return static_cast<std::uint8_t>(get_data_register());
        }
        inline void write_char(const std::uint8_t &ch) noexcept
        {
            reg_write(uart_->DATA, ch);
        }

        inline auto get_write_register_address() noexcept
        {
            return &uart_->DATA;
        }
        inline auto get_read_register_address() noexcept
        {
            return &uart_->DATA;
        }

        inline void irq_enable(const irq_enable_flags_t &enable_flag, const bool &enable) noexcept
        {
            reg_manipulate_bit(uart_->CTRL, imxutility::enum_value(enable_flag), enable);
        }
        inline bool irq_status(const irq_status_flags_t &flag) noexcept
        {
            return reg_get_bit(uart_->STAT, imxutility::enum_value(flag));
        }
        inline void irq_clear(const irq_status_flags_t &clear_flag) noexcept
        {
            reg_set_bit(uart_->STAT, imxutility::enum_value(clear_flag));
        }

        void dma_access_enable(const bool &tx_enable, const bool &rx_enable) noexcept;

    private:
        static void enable_clock(const uart_hw_t uart);

        void hardware_reset() noexcept;

        void fifo_disable() noexcept;

        inline void dma_access_tx_enable(const bool &enable) noexcept
        {
            reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_TDMAE_SHIFT, enable);
        }

        inline void dma_access_rx_enable(const bool &enable) noexcept
        {
            reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_RDMAE_SHIFT, enable);
        }
        inline void tx_enable(const bool &enable) noexcept
        {
            reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_TE_SHIFT, enable);
        }
        inline void rx_enable(const bool &enable) noexcept
        {
            reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_RE_SHIFT, enable);
        }

        void set_baud(const uart_baud_rate_t &baud, const std::uint32_t &uart_clock) noexcept;
        void set_stop_bits(const uart_stop_bit_t &stop_bit) noexcept;
        void set_data_bits(const uart_data_bits_t &data_bits) noexcept;
        void set_parity(const uart_parity_t &parity) noexcept;
        void set_timeout(const uart_timeout_t &timeout) noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_UART_HARDWARE_HPP_