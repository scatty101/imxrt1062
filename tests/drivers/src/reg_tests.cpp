#include "tests.hpp"

#include <limits>

using namespace imxdrivers;
TEST(REG, REG_READ)
{
    constexpr std::uint32_t start_value = 0xfabc;
    volatile std::uint32_t reg = start_value;

    EXPECT_EQ(reg_get(reg), start_value);
}

TEST(REG, REG_SET)
{
    constexpr std::uint32_t set_mask = 0b101101;
    volatile std::uint32_t reg = 0;

    reg_set(reg, set_mask);

    auto expected = reg | set_mask;

    EXPECT_EQ(reg_get(reg), expected);
}

TEST(REG, REG_CLEAR)
{
    constexpr std::uint32_t clear_mask = 0b1110;
    volatile std::uint32_t reg = 0b1111;

    reg_clear(reg, clear_mask);
    auto expected = reg & (~clear_mask);
    EXPECT_EQ(reg_get(reg), expected);
}

TEST(REG, REG_WRITE)
{
    constexpr std::uint32_t write_val = 0xfefefefe;
    volatile std::uint32_t reg = 0xfffff;

    reg_write(reg, write_val);

    EXPECT_EQ(reg_get(reg), write_val);
}

TEST(REG, REG_GET_BIT)
{
    // volatile std::uint32_t reg = 0b1001;

    // EXPECT_TRUE(reg_get_bit(reg, 3));
    // EXPECT_FALSE(reg_get_bit(reg, 2));
    // EXPECT_FALSE(reg_get_bit(reg, 1));
    // EXPECT_TRUE(reg_get_bit(reg, 0));

    volatile std::uint32_t reg = 0xfab12346;

    for (auto bit_pos = 0; bit_pos < std::numeric_limits<std::uint32_t>::digits; ++bit_pos)
    {
        auto bit_value = (reg >> bit_pos) & 0x1;
        EXPECT_EQ(reg_get_bit(reg, bit_pos), bit_value);
    }
}
TEST(REG, REG_CLEAR_BIT)
{
    volatile std::uint32_t reg = 0x12345678;
    auto current = reg;
    for (auto bit_pos = 0; bit_pos < std::numeric_limits<std::uint32_t>::digits; ++bit_pos)
    {
        current &= ~(1 << bit_pos);
        reg_clear_bit(reg, bit_pos);
        EXPECT_FALSE(reg_get_bit(reg, bit_pos));
        EXPECT_EQ(reg_get(reg), current);
    }

    EXPECT_EQ(reg_get(reg), static_cast<std::uint32_t>(0));
}

TEST(REG, REG_SET_BIT)
{
    volatile std::uint32_t reg = 0x1;
    auto current = reg;
    for (auto bit_pos = 0; bit_pos < std::numeric_limits<std::uint32_t>::digits; ++bit_pos)
    {
        current |= (1 << bit_pos);
        reg_set_bit(reg, bit_pos);
        EXPECT_TRUE(reg_get_bit(reg, bit_pos));
        EXPECT_EQ(reg_get(reg), current);
    }

    EXPECT_EQ(reg_get(reg), std::numeric_limits<typeof(reg)>::max());
}
