#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace delete_and_earn {

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }        

        if (nums.size() == 1) {
            return nums[0];
        }

        std::vector<int> counts(10001, 0);
        int maxNum = nums[0];
        for (auto num : nums) {
            counts[num]++;
            if (num > maxNum) {
                maxNum = num;
            }
        }
        
        int one = counts[0];
        int two = max(counts[1], counts[0]);
        int currMax, including;
        for (int i = 2; i <= maxNum; ++i) {
            currMax = 0;
            if (two > currMax) {
                currMax = two;
            }

            including = one + (i * counts[i]);
            if (including > currMax) {
                currMax = including;
            }
            one = two;
            two = currMax;
        }
        return two;
    }
};

struct TestCase {
    vector<int> nums;
    int expected;
};

class DeleteAndEarnTest : public testing::TestWithParam<TestCase> {};

TEST_P(DeleteAndEarnTest, DeleteAndEarn) {
    Solution solution;
    auto nums = GetParam().nums;
    EXPECT_EQ(solution.deleteAndEarn(nums), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    DeleteAndEarnTest,
    testing::Values(
        // LeetCode examples
        TestCase{{3, 4, 2}, 6},
        TestCase{{2, 2, 3, 3, 3, 4}, 9},

        // Smallest inputs
        TestCase{{1}, 1},
        TestCase{{5}, 5},
        TestCase{{10000}, 10000},

        // Two distinct values
        TestCase{{1, 2}, 2},
        TestCase{{2, 3}, 3},
        TestCase{{1, 3}, 4},

        // // Three values
        TestCase{{1, 2, 3}, 4},
        TestCase{{1, 1, 2, 2}, 4},
        TestCase{{2, 2, 3, 3}, 6},

        // // Repeated single value
        TestCase{{5, 5, 5, 5}, 20},
        TestCase{{1, 1, 1, 1, 1}, 5},

        // // Non-adjacent values — take all
        TestCase{{1, 3, 5, 7}, 16},
        TestCase{{10, 20, 30}, 60},

        // // Choose one cluster over adjacent clusters
        TestCase{{1, 1, 4, 4, 4}, 14},
        TestCase{{5, 5, 1, 1, 1}, 13},
        TestCase{{2, 2, 2, 5, 5}, 16},

        // // Longer sequences
        TestCase{{1, 2, 3, 4, 5}, 9},
        TestCase{{1, 2, 3, 4, 5, 6}, 12},
        TestCase{{3, 3, 3, 4, 4, 6, 6, 6}, 27},

        // // Dense duplicates with gaps
        TestCase{{1, 1, 2, 2, 2, 3}, 6},
        TestCase{{1, 2, 2, 3, 3, 3, 4}, 10}
    ));

}  // namespace delete_and_earn
