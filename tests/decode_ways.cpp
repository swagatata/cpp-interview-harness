#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace decode_ways {

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty()) {
            return 0;
        }
        // LeetCode 91: implement here.

        int two = 1, n = s.size();
        int one = (s.back() == '0' ? 0 : 1);
        for (int i = n - 2; i >= 0; --i) {
            int nWays = 0;
            if (s[i] != '0') {
                nWays = one;
            }

            int twoDigit = (s[i] - '0') * 10 + s[i+1] - '0';
            if (twoDigit > 9 && twoDigit < 27) {
                nWays += two;
            }
            two = one;
            one = nWays;
        }
        return one;
    }
};

struct TestCase {
    string s;
    int expected;
};

class DecodeWaysTest : public testing::TestWithParam<TestCase> {};

TEST_P(DecodeWaysTest, NumDecodings) {
    Solution solution;
    EXPECT_EQ(solution.numDecodings(GetParam().s), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    DecodeWaysTest,
    testing::Values(
        // LeetCode examples
        TestCase{"12", 2},
        TestCase{"226", 3},
        TestCase{"06", 0},

        // Single digit
        TestCase{"1", 1},
        TestCase{"9", 1},

        // Leading or standalone zero
        TestCase{"0", 0},
        TestCase{"011", 0},

        // Valid two-digit endings with zero
        TestCase{"10", 1},
        TestCase{"20", 1},

        // Invalid zero splits
        TestCase{"30", 0},
        TestCase{"50", 0},
        TestCase{"60", 0},
        TestCase{"00", 0},
        TestCase{"100", 0},
        TestCase{"1000", 0},
        TestCase{"1001", 0},

        // Zero in the middle with valid prefix
        TestCase{"101", 1},
        TestCase{"110", 1},
        TestCase{"102010", 1},
        TestCase{"808080", 0},

        // Two-digit boundaries (10-26)
        TestCase{"26", 2},
        TestCase{"27", 1},
        TestCase{"99", 1},

        // Repeated ones — Fibonacci-style growth
        TestCase{"111", 3},
        TestCase{"1111", 5},
        TestCase{"11111", 8},

        // Mixed patterns
        TestCase{"11106", 2},
        TestCase{"2101", 1},
        TestCase{"2525", 4},
        TestCase{"112358", 5},
        TestCase{"123456789", 3},

        // Longer input
        TestCase{"1111111111", 89}
    ));

}  // namespace decode_ways
