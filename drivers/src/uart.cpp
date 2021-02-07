#include "uart.hpp"

namespace imxdrivers
{

    uart_handler_t::uart_handler_t(const uart_hw_t _uart, const uart_config_t &_cfg) noexcept : uart_hardware_t::uart_hardware_t(_uart)
    {
        config(_cfg);
        enable(true);
    }
    uart_handler_t::~uart_handler_t() noexcept = default;

    /**
     * @brief Blocking write
     * 
     * @param data 
     */
    inline void uart_handler_t::write(const std::uint8_t &data) noexcept
    {
        while (!tx_empty())
        {
            continue;
        }
        write_char(data);
    }
    inline std::uint8_t uart_handler_t::read() noexcept
    {
        while (!rx_full())
        {
            continue;
        }

        return read_char();
    }

    void uart_handler_t::write(const std::uint8_t *input_buffer, const std::size_t &size) noexcept
    {
        std::uint8_t *start = const_cast<std::uint8_t *>(input_buffer);
        const std::uint8_t *END = input_buffer + size;
        while (start != END)
        {
            write(*start);
            ++start;
        }
    }
    void uart_handler_t::read(const std::uint8_t *output_buffer, const std::size_t &size) noexcept
    {
        std::uint8_t *start = const_cast<std::uint8_t *>(output_buffer);
        const std::uint8_t *END = output_buffer + size;
        while (start != END)
        {
            *start = read();
            start++;
        }
    }

} // namespace imxdrivers