#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace climbing_stairs {

class Solution {
public:
    int climbStairs(int n) {
        // LeetCode 70: implement here.
        if (n < 1)
            return 0;

        if (n == 1)
            return 1;

        int one = 1, two = 1, temp = 0;
        for (int i = 2; i <= n; ++i) {
            temp = one + two;
            one = two;
            two = temp;            
        }
        return temp;
    }
};

struct TestCase {
    int n;
    int expected;
};

class ClimbingStairsTest : public testing::TestWithParam<TestCase> {};

TEST_P(ClimbingStairsTest, ClimbStairs) {
    Solution solution;
    EXPECT_EQ(solution.climbStairs(GetParam().n), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    ClimbingStairsTest,
    testing::Values(
        // LeetCode examples
        TestCase{2, 2},
        TestCase{3, 3},

        // Smallest input
        TestCase{1, 1},

        // Fibonacci sequence: 1, 2, 3, 5, 8, 13, ...
        TestCase{4, 5},
        TestCase{5, 8},
        TestCase{6, 13},
        TestCase{7, 21},
        TestCase{8, 34},
        TestCase{9, 55},
        TestCase{10, 89},

        // Larger values
        TestCase{15, 987},
        TestCase{20, 10946},
        TestCase{30, 1346269},

        // Upper constraint (1 <= n <= 45)
        TestCase{45, 1836311903}
    ));

}  // namespace climbing_stairs
