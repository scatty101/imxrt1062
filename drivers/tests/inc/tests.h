#if !defined IMXDRIVERS_TESTS_H_
#define IMXDRIVERS_TESTS_H_

#include <cstdint>
#include <stdio.h>

#include <hardware.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

constexpr bool TEST_PRINT_ENABLE = false;

#define DEBUG_PRINT         \
    if (TEST_PRINT_ENABLE)  \
    {                       \
        printf(__VA__ARGS); \
    }

#endif // IMXDRIVERS_TESTS_H_