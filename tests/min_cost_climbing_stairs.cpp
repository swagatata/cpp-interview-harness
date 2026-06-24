#include "leetcode.hpp"

#include <gtest/gtest.h>

#include <string>

namespace min_cost_climbing_stairs {

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        // LeetCode 746: implement here.
        (void)cost;
        return 0;
    }
};

struct TestCase {
    const char* name;
    vector<int> cost;
    int expected;
};

class MinCostClimbingStairsTest : public testing::TestWithParam<TestCase> {};

TEST_P(MinCostClimbingStairsTest, MinCostClimbingStairs) {
    Solution solution;
    auto cost = GetParam().cost;
    EXPECT_EQ(solution.minCostClimbingStairs(cost), GetParam().expected)
        << "test case: " << GetParam().name;
}

std::string TestName(const testing::TestParamInfo<TestCase>& info) {
    return info.param.name;
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    MinCostClimbingStairsTest,
    testing::Values(
        // LeetCode examples
        TestCase{"leetcode_example_1_start_at_index_1", {10, 15, 20}, 15},
        TestCase{"leetcode_example_2_skip_expensive_steps", {1, 100, 1, 1, 1, 100, 1, 1, 100, 1}, 6},

        // Smallest inputs (2 <= cost.length)
        TestCase{"two_steps_start_at_cheaper_index_0", {1, 2}, 1},
        TestCase{"two_steps_start_at_cheaper_index_1", {2, 1}, 1},
        TestCase{"two_steps_equal_cost", {5, 5}, 5},
        TestCase{"two_steps_both_zero", {0, 0}, 0},

        // Start position choice
        TestCase{"cheaper_to_start_at_index_1", {100, 1, 1, 1}, 2},
        TestCase{"cheaper_to_start_at_index_0", {1, 100, 1, 1}, 2},
        TestCase{"equal_start_options_three_steps", {3, 3, 3}, 3},

        // All same or zero cost
        TestCase{"all_zeros", {0, 0, 0, 0}, 0},
        TestCase{"all_same_nonzero", {3, 3, 3, 3}, 6},

        // Monotonic costs
        TestCase{"strictly_increasing", {1, 2, 3, 4}, 4},
        TestCase{"strictly_decreasing", {4, 3, 2, 1}, 4},

        // Alternating expensive / cheap steps
        TestCase{"alternating_high_low", {1, 100, 1, 100, 1}, 3},
        TestCase{"alternating_low_high", {100, 1, 100, 1, 100}, 2},

        // Longer paths
        TestCase{"long_cheap_path", {1, 1, 1, 1, 1, 1, 1, 1}, 4},
        TestCase{"single_expensive_spike", {1, 1, 100, 1, 1}, 2},
        TestCase{"two_expensive_spikes", {1, 100, 1, 100, 1, 1}, 3},

        // Larger values within constraints (0 <= cost[i] <= 999)
        TestCase{"max_cost_values", {999, 999, 999, 999}, 1998},
        TestCase{"max_cost_with_zero_escape", {999, 0, 999, 0, 999}, 0}
    ),
    TestName);

}  // namespace min_cost_climbing_stairs
