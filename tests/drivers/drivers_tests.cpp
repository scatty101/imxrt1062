#include <cstdint>
#include <stdio.h>

#include <gtest/gtest.h>
#include <utility.hpp>

#include "clocks.hpp"
#include "timer.hpp"

int main(void)
{
    ::testing::InitGoogleTest();
    auto tests = RUN_ALL_TESTS();

    while (1)
    {
    }

    return 0;
}
