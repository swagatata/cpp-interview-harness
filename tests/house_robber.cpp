#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace house_robber {

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        size_t n = nums.size();
        long long one = 0, two = nums[0];
        for (size_t i = 1; i < n; ++i) {
            long long max = 0;
            // i'm not included
            if (two > max) {
                max = two;
            }

            // i'm included
            long long withme = nums[i];
            if (i >= 2) {
                withme += one;
            }
            if (withme > max) {
                max = withme;
            }

            one = two;
            two = max;
            // cout << "maxat " << i << " is : " << max << endl;
        }

        return two;
    }
};

struct TestCase {
    vector<int> nums;
    int expected;
};

class HouseRobberTest : public testing::TestWithParam<TestCase> {};

TEST_P(HouseRobberTest, Rob) {
    Solution solution;
    auto nums = GetParam().nums;
    EXPECT_EQ(solution.rob(nums), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    HouseRobberTest,
    testing::Values(
        // LeetCode examples
        TestCase{{1, 2, 3, 1}, 4},
        TestCase{{2, 7, 9, 3, 1}, 12},

        // Smallest inputs
        TestCase{{5}, 5},
        TestCase{{2, 3}, 3},
        TestCase{{5, 1}, 5},

        // Three houses
        TestCase{{2, 1, 1}, 3},
        TestCase{{1, 100, 1}, 100},
        TestCase{{100, 1, 100}, 200},

        // Pick every other house
        TestCase{{1, 2, 3, 4, 5}, 9},
        TestCase{{1, 1, 1, 1}, 2},
        TestCase{{5, 5, 5, 5}, 10},

        // Zeros
        TestCase{{0, 0, 0}, 0},
        TestCase{{0, 1, 0, 1}, 2},

        // Alternating high values
        TestCase{{100, 1, 1, 100}, 200},
        TestCase{{2, 1, 1, 2}, 4},

        // Longer street
        TestCase{{4, 1, 2, 7, 5, 3}, 14},
        TestCase{{1, 3, 1, 3, 100}, 103},

        // Larger values within constraints (0 <= nums[i] <= 400)
        TestCase{{400, 0, 400, 0, 400}, 1200},
        TestCase{{10, 20, 30, 40, 50, 60}, 120}
    ));

}  // namespace house_robber
