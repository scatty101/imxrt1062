#include <cstdint>
#include <stdio.h>

#include <gtest/gtest.h>
#include <utility.hpp>

#include "clocks.hpp"

const auto gpt_clocks = GPT_CLOCKS;
const auto gpt_peripheral = GPT_BASE_PTRS;

imxdrivers::clock_t gpt_clock(gpt_clocks, gpt_peripheral);

static void gtest_init();

// Custom delay, cant be better now
inline void custom_delay(const std::uint32_t &delay_cycles = 1)
{
    for (std::uint32_t i = 0; i < delay_cycles; i++)
    {
        asm volatile("nop");
    }
}

constexpr std::uint32_t EXPECTED_CPU_CLOCK = 600 * 1000ul * 1000ul;

std::uint32_t delay_cycles = EXPECTED_CPU_CLOCK / (1000ul); // So it should be around 1s

int main(void)
{
    printf("Hi! Main started\n");
    while (1)
    {
        custom_delay(delay_cycles);
        printf("In while...\n");
    }

    return 0;
}

static void gtest_init()
{
    ::testing::InitGoogleTest();

    auto tests = RUN_ALL_TESTS();
}
