#include "tests.hpp"

#include <utility>
#include <vector>

template <typename T>
using clock_pair_t = std::pair<imxdrivers::clock_hw_t, T>;

template <typename T>
using clock_list_t = std::vector<std::pair<imxdrivers::clock_hw_t, T>>;

template <typename specification_t, typename T>
void test_spec(const std::initializer_list<imxdrivers::clock_hw_t> &clocks, const std::initializer_list<T> &peripherals, const clock_list_t<T> &test_list)
{
    for (auto &elem : test_list)
    {
        specification_t spec(elem.second);
        auto clock = imxdrivers::clock_t::get_clock(clocks, peripherals, spec);
        ASSERT_TRUE(clock);
        EXPECT_EQ(elem.first, *clock);
    }
}

TEST(CLOCKS, GPT_TESTS)
{
    const auto gpt_clocks = GPT_CLOCKS;
    const auto gpt_peripheral = GPT_BASE_PTRS;

    clock_list_t<GPT_Type *> test_clocks;

    test_clocks.push_back(std::make_pair(kCLOCK_Gpt1, GPT1));
    test_clocks.push_back(std::make_pair(kCLOCK_Gpt2, GPT2));

    test_spec<imxdrivers::default_spec_t<typeof(GPT1)>, typeof(GPT1)>(gpt_clocks, gpt_peripheral, test_clocks);
}

TEST(CLOCKS, UART_CLOCKS)
{
    const auto uart_clocks = LPUART_CLOCKS;
    const auto uart_peripherals = LPUART_BASE_PTRS;

    clock_list_t<LPUART_Type *> test_clocks;

    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart1, LPUART1));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart2, LPUART2));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart3, LPUART3));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart4, LPUART4));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart5, LPUART5));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart6, LPUART6));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart7, LPUART7));
    test_clocks.push_back(std::make_pair(kCLOCK_Lpuart8, LPUART8));
    test_spec<imxdrivers::uart_clock_spec_t, typeof(LPUART1)>(uart_clocks, uart_peripherals, test_clocks);
}

TEST(CLOCKS, DMA_MUX_CLOCKS)
{
    const static auto dma_mux_peripherals = DMAMUX_BASE_PTRS;
    const static auto dma_mux_clocks = DMAMUX_CLOCKS;
    clock_list_t<DMAMUX_Type *> test_clocks;
    test_clocks.push_back(std::make_pair(kCLOCK_Dma, DMAMUX));

    test_spec<imxdrivers::dma_mux_clock_spec_t, typeof(DMAMUX)>(dma_mux_clocks, dma_mux_peripherals, test_clocks);
}

TEST(CLOCKS, DMA_CLOCKS)
{
    const static auto dma_peripherals = DMA_BASE_PTRS;
    const static auto dma_clocks = EDMA_CLOCKS;

    clock_list_t<DMA_Type *> test_clocks;
    test_clocks.push_back(std::make_pair(kCLOCK_Dma, DMA0));

    test_spec<imxdrivers::dma_clock_spec_t, typeof(DMA0)>(dma_clocks, dma_peripherals, test_clocks);
}
