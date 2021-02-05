#include "tests.hpp"

#include <utility.hpp>

template <typename T>
class timer_test_t : public imxutility::timer_t<T>
{
public:
    T fake_time = 0;
    timer_test_t() : fake_time(0)
    {
    }

    virtual inline T time_elapsed() noexcept override
    {
        return fake_time;
    }
};

TEST(TIMER, TIMER_DEFAULT_VALUES)
{
    timer_test_t<std::uint32_t> timer;
    /* Timer after start should not be running or expired */
    EXPECT_FALSE(timer.running());
    EXPECT_FALSE(timer.expired());
}

TEST(TIMER, TIMER_CHECK_EXPIRE)
{
    constexpr std::uint32_t EXPIRE_VALUE = 100;
    timer_test_t<std::uint32_t> timer;

    timer.restart(EXPIRE_VALUE);

    /* Now timer should run */
    EXPECT_TRUE(timer.running());
    /* And shouldn't be expired */
    EXPECT_FALSE(timer.expired());

    /* Lets check, when expire will happen */
    timer.fake_time = EXPIRE_VALUE - 1;
    EXPECT_FALSE(timer.expired());

    /* Now expire should trigger once */
    timer.fake_time = EXPIRE_VALUE;
    EXPECT_TRUE(timer.expired());
    EXPECT_FALSE(timer.expired());
}

TEST(TIMER, TIMER_STOP)
{
    constexpr std::uint32_t EXPIRE_VALUE = 153;
    timer_test_t<std::uint32_t> timer;
    timer.restart(EXPIRE_VALUE);

    /* Now timer should run */
    EXPECT_TRUE(timer.running());
    /* And shouldn't be expired */
    EXPECT_FALSE(timer.expired());

    /* Lets set timer to expire time, but then we will stop it */
    timer.fake_time = EXPIRE_VALUE;
    timer.stop();

    EXPECT_FALSE(timer.running());
    EXPECT_FALSE(timer.expired());
}

/* We could create simple template to test value for timers, but i do not consider this needed */

TEST(TIMER, EXPIRE_BIG_VALUES)
{
    /* Considering implementation, I am really interested in big values e.x. 2^31 + 1*/
    constexpr std::uint32_t FAKE_TIME_START_VALUE = std::numeric_limits<std::int32_t>::max();
    constexpr std::uint32_t EXPIRE_VALUE = 5;

    /* So, we starts with fake time == FAKE_TIME_START_VALUE and then we will add 5 to its */
    timer_test_t<std::uint32_t> timer;
    timer.fake_time = FAKE_TIME_START_VALUE;

    timer.restart(EXPIRE_VALUE);

    /* Standard */
    EXPECT_FALSE(timer.expired());
    EXPECT_TRUE(timer.running());

    /* Shouldn't expire now */
    timer.fake_time += (EXPIRE_VALUE - 1);
    EXPECT_FALSE(timer.expired());
    EXPECT_TRUE(timer.running());

    /* Now should expire */
    timer.fake_time += 1;
    EXPECT_TRUE(timer.expired());
    EXPECT_FALSE(timer.running());
}

TEST(TIMER, OVERFLOW_CHECK)
{
    /*We will generate overflow on timer */
    constexpr std::uint32_t OVERFLOW_TIMER_VALUE = std::numeric_limits<std::uint32_t>::max();
    constexpr std::uint32_t EXPIRE_VALUE = 5;

    timer_test_t<std::uint32_t> timer;
    timer.fake_time = OVERFLOW_TIMER_VALUE;

    timer.restart(EXPIRE_VALUE);

    /* Standard */
    EXPECT_FALSE(timer.expired());
    EXPECT_TRUE(timer.running());

    /* Shouldn't expire now */
    timer.fake_time += (EXPIRE_VALUE - 1);
    EXPECT_FALSE(timer.expired());
    EXPECT_TRUE(timer.running());

    /* Now should expire */
    timer.fake_time += 1;
    EXPECT_TRUE(timer.expired());
    EXPECT_FALSE(timer.running());
}
