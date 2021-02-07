#include "uart_hardware.hpp"

#include <imxrt1062/utility.hpp>
#include "reg.hpp"

using namespace imxutility;

namespace imxdrivers
{
    uart_hardware_t::uart_hardware_t(const uart_hw_t _uart, const uart_config_t &_config) noexcept : uart_(_uart)
    {
        uart_hardware_t::enable_clock(_uart);
        config(_config);
    }

    uart_hardware_t::~uart_hardware_t()
    {
    }

    void uart_hardware_t::config(const uart_config_t &cfg) noexcept
    {
        enable(false);

        hardware_reset();
        fifo_disable();

        set_baud(cfg.baud, get_uart_clock());
        set_stop_bits(cfg.stop_bit);
        set_data_bits(cfg.data_bits);
        set_parity(cfg.parity);

        set_timeout(cfg.timeout);
    }

    void uart_hardware_t::set_baud(const uart_baud_rate_t &baud_enum, const std::uint32_t &uart_clock) noexcept
    {
        // SDK implementation
        const std::uint32_t BAUD = enum_value(baud_enum);

        /** 
            * This LPUART instantiation uses a slightly different baud rate calculation
		    * The idea is to use the best OSR (over-sampling rate) possible
	        * Note, OSR is typically hard-set to 16 in other LPUART instantiations
		    * loop to find the best OSR value possible, one that generates minimum baudDiff
		    * iterate through the rest of the supported values of OSR 
        */

        std::uint32_t baud_actual = BAUD;
        std::uint8_t osr = 0U;
        std::uint16_t sbr = 0U;
        for (std::uint8_t osr_tmp = 4U; osr_tmp <= 32U; osr_tmp++)
        {
            /* calculate the temporary sbr value   */
            std::uint16_t sbr_tmp = (uint16_t)((uart_clock * 10U / (BAUD * (uint32_t)osr_tmp) + 5U) / 10U);
            /*set sbrTemp to 1 if the sourceClockInHz can not satisfy the desired baud rate*/
            if (sbr_tmp == 0U)
            {
                sbr_tmp = 1U;
            }
            /* Calculate the baud rate based on the temporary OSR and SBR values */
            std::uint32_t baud_calculated = (uart_clock / ((uint32_t)osr_tmp * (uint32_t)sbr_tmp));
            std::uint32_t diff_tmp = baud_calculated > BAUD ? (baud_calculated - BAUD) : (BAUD - baud_calculated);

            if (diff_tmp <= baud_actual)
            {
                baud_actual = diff_tmp;
                osr = osr_tmp; /* update and store the best OSR value calculated */
                sbr = sbr_tmp; /* update store the best SBR value calculated */
            }
        }

        /* Check to see if actual baud rate is within 3% of desired baud rate
		     * based on the best calculate OSR value */
        if (baud_actual > ((BAUD / 100U) * 3U))
        {
            /* Unacceptable baud rate difference of more than 3%*/
            assert(false);
        }

        /* Acceptable baud rate, check if OSR is between 4x and 7x oversampling.
		     * If so, then "BOTHEDGE" sampling must be turned on */
        if ((osr > 3U) && (osr < 8U))
        {
            reg_write(uart_->BAUD, LPUART_BAUD_BOTHEDGE_MASK);
        }
        /* program the osr value (bit value is one less than actual value) */
        reg_manipulate_mask(uart_->BAUD, LPUART_BAUD_OSR_MASK, LPUART_BAUD_OSR_SHIFT, osr - 1UL);

        /* write the sbr value to the BAUD registers */
        reg_manipulate_mask(uart_->BAUD, LPUART_BAUD_SBR_MASK, LPUART_BAUD_SBR_SHIFT, sbr);
    }
    void uart_hardware_t::set_data_bits(const uart_data_bits_t &data_bits) noexcept
    {
        const bool data_7_bits = data_bits == uart_data_bits_t::data_bits_7;
        const bool data_8_bits = data_bits == uart_data_bits_t::data_bits_8;
        const bool data_9_bits = not data_8_bits;

        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_M7_SHIFT, data_7_bits);
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_M_SHIFT, data_9_bits);
    }
    void uart_hardware_t::set_stop_bits(const uart_stop_bit_t &stop_bit_enum) noexcept
    {
        const bool stop_bit_2 = stop_bit_enum == uart_stop_bit_t::stop_bit_2;
        reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_SBNS_SHIFT, stop_bit_2);
    }

    void uart_hardware_t::set_parity(const uart_parity_t &parity_enum) noexcept
    {
        const bool even = parity_enum == uart_parity_t::even;
        const bool odd = parity_enum == uart_parity_t::odd;

        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_PE_SHIFT, even or odd);
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_PT_SHIFT, odd);
    }

    void uart_hardware_t::enable(const bool &enable) noexcept
    {
        tx_enable(enable);
        rx_enable(enable);
    }

    inline void uart_hardware_t::tx_enable(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_TE_SHIFT, enable);
    }
    inline void uart_hardware_t::rx_enable(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_RE_SHIFT, enable);
    }

    void uart_hardware_t::debug(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_LOOPS_SHIFT, enable);
    }

    inline bool uart_hardware_t::tx_empty() noexcept
    {
        return irq_status(irq_status_flags_t::tx_empty);
    }
    inline bool uart_hardware_t::rx_full() noexcept
    {
        return irq_status(irq_status_flags_t::rx_full);
    }

    void uart_hardware_t::dma_access_enable(const bool &tx_enable, const bool &rx_enable) noexcept
    {
        dma_access_tx_enable(tx_enable);
        dma_access_rx_enable(rx_enable);
    }

    inline void uart_hardware_t::dma_access_tx_enable(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_TDMAE_SHIFT, enable);
    }

    inline void uart_hardware_t::dma_access_rx_enable(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_RDMAE_SHIFT, enable);
    }

    void uart_hardware_t::hardware_reset() noexcept
    {
        reg_set(uart_->GLOBAL, LPUART_GLOBAL_RST_MASK);
        data_sync();
        reg_clear(uart_->GLOBAL, LPUART_GLOBAL_RST_MASK);
    }

    void uart_hardware_t::fifo_disable() noexcept
    {
        /*fifo flush and disable */
        reg_set(uart_->FIFO, LPUART_FIFO_RXFLUSH_MASK | LPUART_FIFO_TXFLUSH_MASK);

        reg_clear_bit(uart_->FIFO, LPUART_FIFO_RXFE_SHIFT);
        reg_clear_bit(uart_->FIFO, LPUART_FIFO_TXFE_SHIFT);
    }

    inline std::uint32_t uart_hardware_t::get_data_register() noexcept
    {
        return reg_get(uart_->CTRL);
    }
    inline std::uint8_t uart_hardware_t::read_char() noexcept
    {
        return static_cast<std::uint8_t>(get_data_register());
    }
    inline void uart_hardware_t::put_char(const std::uint8_t &ch) noexcept
    {
        reg_write(uart_->DATA, ch);
    }

    inline auto uart_hardware_t::get_write_register_address() noexcept
    {
        return &uart_->DATA;
    }
    inline auto uart_hardware_t::get_read_register_address() noexcept
    {
        return &uart_->DATA;
    }

    inline void uart_hardware_t::irq_enable(const irq_enable_flags_t &enable_flag, const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->CTRL, enum_value(enable_flag), enable);
    }
    inline bool uart_hardware_t::irq_status(const irq_status_flags_t &flag) noexcept
    {
        return reg_get_bit(uart_->STAT, enum_value(flag));
    }
    inline void uart_hardware_t::irq_clear(const irq_status_flags_t &clear_flag) noexcept
    {
        reg_set_bit(uart_->STAT, enum_value(clear_flag));
    }

    void uart_hardware_t::enable_clock(const uart_hw_t uart)
    {
        const static auto uart_peripherals = LPUART_BASE_PTRS;
        const static auto uart_clocks = LPUART_CLOCKS;

        uart_clock_spec_t spec(uart);

        auto clock = clock_t::get_clock(uart_clocks, uart_peripherals, spec);

        imxdrivers::enable_clock(*clock);
    }
} // namespace imxdrivers
