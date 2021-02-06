#include "uart_hardware.hpp"

#include "clocks.hpp"
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
    }

    void uart_hardware_t::enable(const bool &enable) noexcept
    {
    }
    void uart_hardware_t::debug(const bool &enable) noexcept
    {
    }

    inline bool uart_hardware_t::tx_empty() noexcept
    {
    }
    inline bool uart_hardware_t::rx_full() noexcept
    {
    }

    void uart_hardware_t::dma_access_enable(const bool &tx_enable, const bool &rx_enable) noexcept
    {
    }

    inline void uart_hardware_t::dma_access_tx_enable(const bool &enable) noexcept
    {
    }

    inline void uart_hardware_t::dma_access_rx_enable(const bool &enable) noexcept
    {
    }

    void uart_hardware_t::enable_clock(const uart_hw_t uart)
    {
        const static auto uart_peripherals = LPUART_BASE_PTRS;
        const static auto uart_clocks = LPUART_CLOCKS;

        default_specification spec(uart);

        auto clock = clock_t::get_clock(uart_clocks, uart_peripherals, spec);

        imxdrivers::enable_clock(*clock);
    }
} // namespace imxdrivers
