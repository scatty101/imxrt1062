#include "tests.hpp"

#include <utility>
#include <array>

imxdrivers::dma_t test_dma(0);

constexpr static std::uint32_t DMA_TEST_SIZE = 5;
std::array<std::uint32_t, DMA_TEST_SIZE> DMA_BUFFER_SECTION(src_arr);
std::array<std::uint32_t, DMA_TEST_SIZE> DMA_BUFFER_SECTION(dst_arr);

TEST(DMA, SINGLE_MEM_TRANSFER)
{
    imxdrivers::dma_channel_t cfg(src_arr.data(), dst_arr.data(), src_arr.size(), imxdrivers::dma_transfer_t::memory_to_memory);

    std::uint32_t test_val = 0;
    for (auto &data : src_arr)
    {
        data = ++test_val;
    }

    dst_arr.fill(0);

    test_dma.config(cfg);

    test_dma.start();

    while (!test_dma.done())
        continue;

    EXPECT_EQ(src_arr, dst_arr);
}
