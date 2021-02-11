#include "tests.hpp"

#include <utility>

imxdrivers::dma_t test_dma(0);

TEST(DMA, CHANNEL_CONFIG)
{
    std::uint32_t src = 153;
    std::uint32_t dst = 0;
    imxdrivers::dma_channel_t cfg_2(&src, &dst, 1, imxdrivers::dma_transfer_t::memory_to_memory);

    test_dma.config(cfg_2);

    test_dma.start();

    while (!test_dma.done())
        continue;

    imxdrivers::sleep(10);

    EXPECT_EQ(src, dst);
}