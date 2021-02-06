#include "tests.hpp"

#include <inc/clocks.hpp>
#include <utility>
#include <vector>

TEST(CLOCKS, GPT_TESTS)
{
    const auto gpt_clocks = GPT_CLOCKS;
    const auto gpt_peripheral = GPT_BASE_PTRS;

    imxdrivers::clock_t gpt(gpt_clocks, gpt_peripheral);

    using pair_t = std::pair<imxdrivers::clock_hw_t, GPT_Type *>;

    std::vector<pair_t> test_clocks;

    test_clocks.push_back(std::make_pair(kCLOCK_Gpt1, GPT1));
    test_clocks.push_back(std::make_pair(kCLOCK_Gpt2, GPT2));

    for (auto &elem : test_clocks)
    {
        imxdrivers::default_specification spec(elem.second);
        EXPECT_EQ(elem.first, gpt.get_clock(spec));
    }
}
