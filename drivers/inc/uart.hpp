#ifndef IMXRT_DRIVERS_UART_HPP_
#define IMXRT_DRIVERS_UART_HPP_

#include "uart_hardware.hpp"
namespace imxdrivers
{
    class uart_handler_t : public uart_hardware_t
    {
    public:
        uart_handler_t(const uart_handler_t &) = delete;
        uart_handler_t &operator=(const uart_handler_t &) = delete;

        uart_handler_t(const uart_hw_t _uart, const uart_config_t &_cfg) noexcept;
        ~uart_handler_t() noexcept;

        inline void write(const std::uint8_t &data) noexcept;
        inline std::uint8_t read() noexcept;

        void write(const std::uint8_t *input_buffer, const std::size_t &size) noexcept;
        void read(const std::uint8_t *output_buffer, const std::size_t &size) noexcept;
    };

} // namespace imxdrivers

#endif // IMXRT_DRIVERS_UART_HPP_