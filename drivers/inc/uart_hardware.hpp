#ifndef IMXRT_DRIVERS_UART_HARDWARE_HPP_
#define IMXRT_DRIVERS_UART_HARDWARE_HPP_

#include <cstdint>

#include <hardware.hpp>

namespace imxdrivers
{
    using uart_hw_t = LPUART_Type *;

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

    };

    enum class uart_parity_t
    {

    };

    enum class uart_data_bits_t
    {

    };

    struct uart_config_t
    {
        uart_baud_rate_t baud;
        uart_stop_bit_t stop_bit;
        uart_parity_t parity;
        uart_data_bits_t data_bits;
    };

    class uart_hardware_t
    {
        const uart_hw_t uart_;

    public:
        uart_hardware_t(const uart_hardware_t &) = delete;
        uart_hardware_t &operator=(const uart_hardware_t &) = delete;

        uart_hardware_t(const uart_hw_t _uart, const uart_config_t &_config);
        ~uart_hardware_t();

        void config(const uart_config_t &cfg) noexcept;
        void enable(const bool &enable) noexcept;
        void debug(const bool &enable) noexcept;

        inline bool tx_empty() noexcept;
        inline bool rx_full() noexcept;

        void dma_access_enable(const bool &tx_enable, const bool &rx_enable) noexcept;
    };
} // namespace imxdrivers

#endif // IMXRT_DRIVERS_UART_HARDWARE_HPP_