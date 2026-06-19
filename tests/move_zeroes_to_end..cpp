#include <gtest/gtest.h>

class Solution {
public:
    void moveZeroesToEnd(std::vector<int>& v) {
        if (v.empty())
            return;
        size_t l = 0, r;
        while (l < v.size()) {
            while (l < v.size() && v[l] != 0) {
                l++;
            }
            r = l + 1;
            while (r < v.size() && v[r] == 0) r++;

            if (r >= v.size())
                break;

            std::swap(v[l], v[r]);
            l++;
        }
    }
};

class MoveZeroesToEndTest : public ::testing::Test {
protected:
    Solution s;
};

TEST_F(MoveZeroesToEndTest, Empty) {
    std::vector<int> v;
    s.moveZeroesToEnd(v);
    EXPECT_TRUE(v.empty());
}

TEST_F(MoveZeroesToEndTest, Basic) {
    std::vector<int> v{0, 1};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 0}));
}

TEST_F(MoveZeroesToEndTest, NonBasic) {
    std::vector<int> v{0, 1, 0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, SingleElementZero) {
    std::vector<int> v{0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{0}));
}

TEST_F(MoveZeroesToEndTest, SingleElementNonZero) {
    std::vector<int> v{42};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{42}));
}

TEST_F(MoveZeroesToEndTest, NoZeroes) {
    std::vector<int> v{3, 1, 4, 1, 5};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{3, 1, 4, 1, 5}));
}

TEST_F(MoveZeroesToEndTest, AllZeroes) {
    std::vector<int> v{0, 0, 0, 0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{0, 0, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, ZeroesAlreadyAtEnd) {
    std::vector<int> v{1, 2, 3, 0, 0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, LeetCodeExample) {
    std::vector<int> v{0, 1, 0, 3, 12};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 3, 12, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, LeadingZeroes) {
    std::vector<int> v{0, 0, 1, 2, 3};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, AlternatingZeroes) {
    std::vector<int> v{0, 1, 0, 2, 0, 3};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 0, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, OneNonZeroSurroundedByZeroes) {
    std::vector<int> v{0, 0, 7, 0, 0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{7, 0, 0, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, DuplicateNonZeroes) {
    std::vector<int> v{0, 1, 1, 0, 2, 2, 0};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{1, 1, 2, 2, 0, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, NegativeNumbersUnchanged) {
    std::vector<int> v{-1, 0, -2, 0, 3};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{-1, -2, 3, 0, 0}));
}

TEST_F(MoveZeroesToEndTest, SingleZeroInMiddle) {
    std::vector<int> v{5, 6, 0, 7, 8};
    s.moveZeroesToEnd(v);
    EXPECT_EQ(v, (std::vector<int>{5, 6, 7, 8, 0}));
}