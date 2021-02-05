#include "tests.hpp"

#include <utility.hpp>

template <typename T>
using edge_test_t = imxutility::edge_t<T>;

TEST(EDGE, NO_EDGE_AFTER_INIT)
{
    edge_test_t<bool> bool_edge;
    EXPECT_FALSE(bool_edge.falling_edge());
    EXPECT_FALSE(bool_edge.rising_edge());
}

TEST(EDGE, DETECT_RISING_EDGE_ONCE)
{
    edge_test_t<bool> bool_edge;

    /* We should detect change now */
    EXPECT_TRUE(bool_edge.detect(true));
    /* Expected change is rising edge, as start state should be "0" */
    EXPECT_TRUE(bool_edge.rising_edge());
    EXPECT_FALSE(bool_edge.falling_edge());

    /* After next detect we shouldn't have any edge */
    EXPECT_FALSE(bool_edge.detect(true));
    EXPECT_FALSE(bool_edge.rising_edge());
    EXPECT_FALSE(bool_edge.falling_edge());
}

TEST(EDGE, DETECT_FALLING_EDGE_ONCE)
{
    edge_test_t<bool> bool_edge;

    /* We should detect change now */
    EXPECT_TRUE(bool_edge.detect(true));
    /* Expected change is rising edge, as start state should be "0" */
    EXPECT_TRUE(bool_edge.rising_edge());
    EXPECT_FALSE(bool_edge.falling_edge());

    /* Now lets try with falling edge */
    EXPECT_TRUE(bool_edge.detect(false));
    EXPECT_FALSE(bool_edge.rising_edge());
    EXPECT_TRUE(bool_edge.falling_edge());
}

TEST(EDGE, DETECT_CHANGE_ON_WORD_TYPE)
{
    edge_test_t<int> int_edge;
    constexpr int DETECT_VALUE = 153;
    /* Well, we should detect change, since start should be 0 */
    EXPECT_TRUE(int_edge.detect(DETECT_VALUE));

    /* We shouldn't expect 'falling' or 'rising edge' since it is int. We can base on 'detect' return */
    // EXPECT_TRUE(int_edge.rising_edge());
    // EXPECT_TRUE(int_edge.falling_edge());

    /* Lets check detect with the same value */
    EXPECT_FALSE(int_edge.detect(DETECT_VALUE));

    /* And now different values */
    EXPECT_TRUE(int_edge.detect(DETECT_VALUE + 1));
    EXPECT_TRUE(int_edge.detect(DETECT_VALUE + 2));
}
