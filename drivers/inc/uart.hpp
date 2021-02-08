#ifndef IMXRT_DRIVERS_UART_HPP_
#define IMXRT_DRIVERS_UART_HPP_

#include "uart_hardware.hpp"
#include "mux.hpp"
namespace imxdrivers
{
    class uart_handler_t : public uart_hardware_t
    {
    public:
        uart_handler_t(const uart_handler_t &) = delete;
        uart_handler_t &operator=(const uart_handler_t &) = delete;

        uart_handler_t(const uart_hw_t _uart, const uart_config_t &_cfg) noexcept;
        ~uart_handler_t() noexcept;

        void write(std::uint8_t *input_buffer, const std::size_t &size) noexcept;
        void read(std::uint8_t *output_buffer, const std::size_t &size) noexcept;

        inline void write(const std::uint8_t &data) noexcept
        {
            while (!tx_empty())
            {
                continue;
            }
            write_char(data);
        }
        inline std::uint8_t read() noexcept
        {
            while (!rx_full())
            {
                continue;
            }

            return read_char();
        }

        constexpr static pad_config_t tx_pad_config() noexcept
        {
            constexpr pad_config_t UART_TX_CONFIG =
                {
                    .slew_rate = slew_rate_t::slow,
                    .drive_strength = drive_strength_t::r0_4,
                    .speed = pin_speed_t::fast_150MHz,
                    .open_drain_enable = open_drain_t::disabled,
                    .pull_keep_enable = pull_keep_enable_t::enabled,
                    .pull_keep_select = pull_keep_select_t::pull,
                    .pull = pull_t::pullup_47k,
                    .hyst = hysterisis_t::disabled,
                };

            return UART_TX_CONFIG;
        }
        constexpr static pad_config_t rx_pad_config() noexcept
        {
            return tx_pad_config();
        }
    };
} // namespace imxdrivers

#endif // IMXRT_DRIVERS_UART_HPP_