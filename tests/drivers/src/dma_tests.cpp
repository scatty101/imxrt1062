#include "tests.hpp"

#include <utility>
#include <array>

imxdrivers::dma_t test_dma(0);
constexpr static std::uint32_t MANY_TESTS_SIZE = 100;
constexpr static std::uint32_t DMA_TEST_BUFFER_SIZE = 255;

template <typename T>
using dma_transfer_test_t = std::array<T, DMA_TEST_BUFFER_SIZE>;

dma_transfer_test_t<std::uint32_t> DMA_BUFFER_SECTION(src_arr_32);
dma_transfer_test_t<std::uint32_t> DMA_BUFFER_SECTION(dst_arr_32);

dma_transfer_test_t<std::uint16_t> DMA_BUFFER_SECTION(src_arr_16);
dma_transfer_test_t<std::uint16_t> DMA_BUFFER_SECTION(dst_arr_16);

dma_transfer_test_t<std::uint8_t> DMA_BUFFER_SECTION(src_arr_8);
dma_transfer_test_t<std::uint8_t> DMA_BUFFER_SECTION(dst_arr_8);

imxdrivers::dma_channel_t DMA_BUFFER_SECTION(sga_test_cfg);

template <typename T>
imxdrivers::dma_channel_t get_transfer_cfg(T *src, T *dst, std::uint16_t transfer_size, imxdrivers::dma_transfer_t transfer_type, imxdrivers::dma_channel_t *next_cfg)
{
    return imxdrivers::dma_channel_t{src, dst, transfer_size, transfer_type, next_cfg};
}

template <typename T>
void test_mem_transfer(T *src, T *dst, std::uint16_t transfer_size, imxdrivers::dma_channel_t *next_cfg = nullptr)
{
    auto cfg = get_transfer_cfg(src, dst, transfer_size, imxdrivers::dma_transfer_t::memory_to_memory, next_cfg);

    // Channel should be disabled
    EXPECT_FALSE(test_dma.busy());

    test_dma.config(cfg);

    // Still busy
    EXPECT_FALSE(test_dma.busy());

    test_dma.start();

    // Channel is transfering now
    EXPECT_TRUE(test_dma.busy());

    while (!test_dma.done())
    {
        continue;
    }

    // After that busy is gone
    EXPECT_FALSE(test_dma.busy());

    for (std::uint16_t i = 0; i < transfer_size; i++)
    {
        EXPECT_EQ(src[i], dst[i]);
    }
}

template <typename T>
void prepare_test_buffer(T *src, T *dst, std::uint16_t size)
{
    for (std::uint16_t i = 0; i < size; i++)
    {
        src[i] = static_cast<T>(i + 1);
        dst[i] = 0;
    }
}

template <typename T>
void prepare_and_test(T *src, T *dst, std::uint16_t transfer_size, imxdrivers::dma_channel_t *next_cfg = nullptr)
{
    prepare_test_buffer(src, dst, transfer_size);
    test_mem_transfer(src, dst, transfer_size, next_cfg);
}

TEST(DMA, MANY_MEM_TRANSFER_8)
{
    auto tests = MANY_TESTS_SIZE;
    while (tests--)
    {
        prepare_and_test(src_arr_8.data(), dst_arr_8.data(), src_arr_8.size());
    }
}
TEST(DMA, MANY_MEM_TRANSFER_16)
{
    auto tests = MANY_TESTS_SIZE;
    while (tests--)
    {
        prepare_and_test(src_arr_16.data(), dst_arr_16.data(), src_arr_16.size());
    }
}
TEST(DMA, MANY_MEM_TRANSFER_32)
{
    auto tests = MANY_TESTS_SIZE;
    while (tests--)
    {
        prepare_and_test(src_arr_32.data(), dst_arr_32.data(), src_arr_32.size());
    }
}

TEST(DMA, SGA_TRANSFER_MUST_USE_NONCACHE_CFG)
{
    // Preparing second buffer
    prepare_test_buffer(src_arr_16.data(), dst_arr_16.data(), src_arr_16.size());
    // Preparing cfg for second buffer transfer
    sga_test_cfg = get_transfer_cfg(src_arr_16.data(), dst_arr_16.data(), src_arr_16.size(), imxdrivers::dma_transfer_t::memory_to_memory, nullptr);

    // Calls test method with next cfg to be applied to dma
    prepare_and_test(src_arr_8.data(), dst_arr_8.data(), src_arr_8.size(), &sga_test_cfg);

    // After test, second transfer should be done also
    EXPECT_EQ(src_arr_16, dst_arr_16);
}