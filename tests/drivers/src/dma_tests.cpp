#include "tests.hpp"

#include <utility>

TEST(DMA, CHANNEL_CONFIG)
{
    std::uint32_t src;
    std::uint32_t dst;
    imxdrivers::dma_channel_t cfg_2(&src, &dst, 1, imxdrivers::dma_transfer_t::memory_to_memory);
}