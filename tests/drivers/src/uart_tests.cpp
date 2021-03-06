#include "tests.hpp"

using namespace imxdrivers;

uart_config_t uart_cfg =
    {
        .baud = uart_baud_rate_t::baud_115200,
        .stop_bit = uart_stop_bit_t::stop_bit_1,
        .parity = uart_parity_t::none,
        .data_bits = uart_data_bits_t::data_bits_8,
        .timeout = uart_timeout_t::timeout_1_char,
};

uart_handler_t test_uart(LPUART1, uart_cfg);
// AD_B0_12 TXD
// AD_B0_13 RXD

pin_mux_t uart_tx_pin{
    {IOMUXC_GPIO_AD_B0_12_LPUART1_TX, false},
    {uart_handler_t::tx_pad_config()},
};

pin_mux_t uart_rx_pin{
    {IOMUXC_GPIO_AD_B0_13_LPUART1_RX, false},
    {uart_handler_t::rx_pad_config()},
};

TEST(UART_HANDLER, UART_ENABLED_AFTER_INIT)
{
    constexpr char TEST_CHAR = 'B';
    test_uart.debug(true);

    test_uart.write(TEST_CHAR);
    auto data = test_uart.read();

    EXPECT_EQ(TEST_CHAR, data);
}

TEST(UART_HANDLER, TRANSFER_A_LOT_OF_CHARS)
{
    char TEST_ARRAY[255];
    char ch = 0;
    for (auto &data : TEST_ARRAY)
    {
        data = ch++;
    }

    test_uart.debug(true);

    for (auto &data : TEST_ARRAY)
    {
        test_uart.write(data);
        EXPECT_EQ(data, test_uart.read());
    }
}