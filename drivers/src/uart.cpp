#include "uart.hpp"

namespace imxdrivers
{

    uart_handler_t::uart_handler_t(const uart_hw_t _uart, const uart_config_t &_cfg) noexcept : uart_hardware_t::uart_hardware_t(_uart)
    {
        config(_cfg);
        enable(true);
    }
    uart_handler_t::~uart_handler_t() noexcept = default;

    void uart_handler_t::write(std::uint8_t *input_buffer, const std::size_t &size) noexcept
    {
        const std::uint8_t *END = input_buffer + size;
        while (input_buffer != END)
        {
            write(*input_buffer);
            ++input_buffer;
        }
    }
    void uart_handler_t::read(std::uint8_t *output_buffer, const std::size_t &size) noexcept
    {
        const std::uint8_t *END = output_buffer + size;
        while (output_buffer != END)
        {
            *output_buffer = read();
            output_buffer++;
        }
    }
} // namespace imxdrivers