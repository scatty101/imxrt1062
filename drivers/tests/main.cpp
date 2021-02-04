#include <cstdint>
#include <stdio.h>

#include <gtest/gtest.h>
#include <utility.hpp>

#include "clocks.hpp"

int main(void)
{
    printf("Test printf?\n");
    ::testing::InitGoogleTest();
    auto tests = RUN_ALL_TESTS();

    while (1)
    {
    }

    return 0;
}
