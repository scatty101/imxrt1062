#if !defined IMXUTILITY_TESTS_HPP_
#define IMXUTILITY_TESTS_HPP_

#include <cstdint>
#include <stdio.h>

#include <hardware.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

constexpr bool TEST_PRINT_ENABLE = false;

#define DEBUG_PRINT         \
    if (TEST_PRINT_ENABLE)  \
    {                       \
        printf(__VA__ARGS); \
    }

#endif // IMXUTILITY_TESTS_HPP_