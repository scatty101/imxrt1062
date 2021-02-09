#include "uart_hardware.hpp"

using namespace imxutility;

namespace imxdrivers
{
    /**
    * @brief Construct a new uart hardware t object
    * 
    * @param _uart 
    */
    uart_hardware_t::uart_hardware_t(const uart_hw_t _uart) noexcept : uart_(_uart)
    {
        uart_hardware_t::enable_clock(_uart);
    }

    /**
     * @brief Destroy the uart hardware t::uart hardware t object
     * 
     */
    uart_hardware_t::~uart_hardware_t()
    {
    }
    /**
     * @brief Config for uart. It also disable uart tx and rx, so after calling this method it must be explicitly enabled
     * 
     * @param cfg 
     */
    void uart_hardware_t::config(const uart_config_t &cfg) noexcept
    {
        imxdrivers::enable_clock(kCLOCK_Lpuart1);
        enable(false);

        hardware_reset();
        fifo_disable();

        set_baud(cfg.baud, get_uart_clock());
        set_stop_bits(cfg.stop_bit);
        set_data_bits(cfg.data_bits);
        set_parity(cfg.parity);

        set_timeout(cfg.timeout);

        uart_->WATER = (LPUART_WATER_RXWATER(1) | LPUART_WATER_TXWATER(1));
    }
    /**
     * @brief Sets hardware to specified baud_enum 
     * 
     * @param baud_enum 
     * @param uart_clock 
     */
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

    /**
     * @brief Sets data bits config in hardware
     * 
     * @param data_bits 
     */
    void uart_hardware_t::set_data_bits(const uart_data_bits_t &data_bits) noexcept
    {
        const bool data_7_bits = data_bits == uart_data_bits_t::data_bits_7;
        const bool data_8_bits = data_bits == uart_data_bits_t::data_bits_8;
        const bool data_9_bits = not data_8_bits;

        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_M7_SHIFT, data_7_bits);
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_M_SHIFT, data_9_bits);
    }
    /**
     * @brief Set stop bits config in hardware
     * 
     * @param stop_bit_enum 
     */
    void uart_hardware_t::set_stop_bits(const uart_stop_bit_t &stop_bit_enum) noexcept
    {
        const bool stop_bit_2 = stop_bit_enum == uart_stop_bit_t::stop_bit_2;
        reg_manipulate_bit(uart_->BAUD, LPUART_BAUD_SBNS_SHIFT, stop_bit_2);
    }
    /**
     * @brief Sets parity config in hardware
     * 
     * @param parity_enum 
     */
    void uart_hardware_t::set_parity(const uart_parity_t &parity_enum) noexcept
    {
        const bool even = parity_enum == uart_parity_t::even;
        const bool odd = parity_enum == uart_parity_t::odd;

        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_PE_SHIFT, even or odd);
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_PT_SHIFT, odd);
    }
    /**
     * @brief Sets rx timeout config in hardware
     * 
     * @param timeout_enum 
     */
    void uart_hardware_t::set_timeout(const uart_timeout_t &timeout_enum) noexcept
    {
        auto timeout = enum_value(timeout_enum);
        reg_manipulate_mask(uart_->CTRL, LPUART_CTRL_IDLECFG_MASK, LPUART_CTRL_IDLECFG_SHIFT, timeout);
    }
    /**
     * @brief Enables / disables tx and rx
     * 
     * @param enable 
     */
    void uart_hardware_t::enable(const bool &enable) noexcept
    {
        tx_enable(enable);
        rx_enable(enable);
    }

    /**
     * @brief Enables / disables debug mode
     * 
     * In debug mode RX is connected to TX.
     * 
     * @param enable 
     */
    void uart_hardware_t::debug(const bool &enable) noexcept
    {
        reg_manipulate_bit(uart_->CTRL, LPUART_CTRL_LOOPS_SHIFT, enable);
    }

    /**
     * @brief Enable access for DMA to access hardware uart registers
     * 
     * @param tx_enable 
     * @param rx_enable 
     */
    void uart_hardware_t::dma_access_enable(const bool &tx_enable, const bool &rx_enable) noexcept
    {
        dma_access_tx_enable(tx_enable);
        dma_access_rx_enable(rx_enable);
    }

    /**
     * @brief Hardware reset of peripheral
     * 
     */
    void uart_hardware_t::hardware_reset() noexcept
    {
        reg_set(uart_->GLOBAL, LPUART_GLOBAL_RST_MASK);
        data_sync();
        reg_clear(uart_->GLOBAL, LPUART_GLOBAL_RST_MASK);
    }

    /**
     * @brief Disables internal fifo for LPUART
     * 
     */
    void uart_hardware_t::fifo_disable() noexcept
    {
        /*fifo flush and disable */
        reg_set(uart_->FIFO, LPUART_FIFO_RXFLUSH_MASK | LPUART_FIFO_TXFLUSH_MASK);

        reg_clear_bit(uart_->FIFO, LPUART_FIFO_RXFE_SHIFT);
        reg_clear_bit(uart_->FIFO, LPUART_FIFO_TXFE_SHIFT);
    }
    /**
     * @brief Enables needed clock
     * 
     * @param uart 
     */
    void uart_hardware_t::enable_clock(const uart_hw_t uart)
    {
        const static auto uart_peripherals = LPUART_BASE_PTRS;
        const static auto uart_clocks = LPUART_CLOCKS;

        uart_clock_spec_t spec(uart);

        auto clock = clock_t::get_clock(uart_clocks, uart_peripherals, spec);

        imxdrivers::enable_clock(*clock);
    }
} // namespace imxdrivers
