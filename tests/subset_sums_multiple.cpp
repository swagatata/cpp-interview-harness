#include <gtest/gtest.h>

#include <functional>
#include <vector>

class Solution {
public:
    Solution(int K) : d_k(K) {}

    inline int mod(int x) {
        if ((x % d_k) >= 0)
            return x % d_k;

        return (x % d_k) + d_k;
    }

    int nSubsetsWithMultiple(std::vector<int> v) {
        if (v.empty())
            return 0;

        if (v.size() == 1)
            return (v[0] % d_k) == 0;

        int totalSubsets = 0;
        size_t n = v.size();
        // std::vector<std::vector<int>> sums(d_k, std::vector<int>(n, 0));
        std::vector<int> next(d_k, 0);
        std::vector<int> curr(d_k, 0);

        next[mod(v[n-1])]++;
        totalSubsets += next[0];
        for (int j = n-2; j >= 0; --j) {
            int modulus = mod(v[j]);
            // int prevModulus = mod(v[j-1]);
            // curr[modulus] = 1 + next[0];

            for (int i = 0; i < d_k; ++i) {
                curr[i] = next[mod(i - modulus)];
            }
            // curr[0] = next[d_k - modulus];
            // curr[d_k - prevModulus] = next[mod(d_k - prevModulus - modulus)];
            curr[modulus]++;

            totalSubsets += curr[0];

            for (int i = 0; i < d_k; ++i) {
                next[i] = curr[i];
                curr[i] = 0;
            }
        }
        // totalSubsets += next[d_k - mod(v[0])];
        return totalSubsets;
    }
private:
    int d_k;
};

namespace {

int modResidue(int x, int k) {
    const int r = x % k;
    return r >= 0 ? r : r + k;
}

int countSubarraysBruteForce(const std::vector<int>& v, int k) {
    const int n = static_cast<int>(v.size());
    int count = 0;

    for (int start = 0; start < n; ++start) {
        int sum = 0;
        for (int end = start; end < n; ++end) {
            sum += v[end];
            if (modResidue(sum, k) == 0)
                ++count;
        }
    }

    return count;
}

}  // namespace

class SubsetSumsMultipleTest : public ::testing::Test {
protected:
    Solution s5{5};
    Solution s2{2};
    Solution s3{3};
    Solution s1{1};
};

TEST_F(SubsetSumsMultipleTest, Empty) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({}), 0);
}

TEST_F(SubsetSumsMultipleTest, SingleElement) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({5}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({10}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({0}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({2}), 0);
    EXPECT_EQ(s5.nSubsetsWithMultiple({-5}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({-2}), 0);
    EXPECT_EQ(s3.nSubsetsWithMultiple({7}), 0);
    EXPECT_EQ(s3.nSubsetsWithMultiple({9}), 1);
}

TEST_F(SubsetSumsMultipleTest, ModulusFive) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({2, 3}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({2, 3, 5}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({2, 3, 0, 5}), 6);
    EXPECT_EQ(s5.nSubsetsWithMultiple({1, 2, 3, 4}), 2);
    EXPECT_EQ(s5.nSubsetsWithMultiple({10, 20}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({1, 1, 3}), 1);
}

TEST_F(SubsetSumsMultipleTest, ContainsZero) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({0, 5}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({0, 0}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({0, 0, 0}), 6);
    EXPECT_EQ(s5.nSubsetsWithMultiple({0, 2, 3}), 3);
    EXPECT_EQ(s2.nSubsetsWithMultiple({0, 1}), 1);
}

TEST_F(SubsetSumsMultipleTest, ModulusTwo) {
    EXPECT_EQ(s2.nSubsetsWithMultiple({1, 2, 3, 4}), 4);
    EXPECT_EQ(s2.nSubsetsWithMultiple({1, 3, 5}), 2);
    EXPECT_EQ(s2.nSubsetsWithMultiple({2, 4, 6}), 6);
    EXPECT_EQ(s2.nSubsetsWithMultiple({1, 1}), 1);
}

TEST_F(SubsetSumsMultipleTest, ModulusThree) {
    EXPECT_EQ(s3.nSubsetsWithMultiple({1, 1, 1}), 1);
    EXPECT_EQ(s3.nSubsetsWithMultiple({1, 2, 3}), 3);
    EXPECT_EQ(s3.nSubsetsWithMultiple({3, 6, 9}), 6);
}

TEST_F(SubsetSumsMultipleTest, ModulusOne) {
    EXPECT_EQ(s1.nSubsetsWithMultiple({42}), 1);
    EXPECT_EQ(s1.nSubsetsWithMultiple({1, 2, 3}), 6);
    EXPECT_EQ(s1.nSubsetsWithMultiple({-1, 0, 5}), 6);
}

TEST_F(SubsetSumsMultipleTest, NegativeNumbers) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({-2, 3}), 0);
    EXPECT_EQ(s5.nSubsetsWithMultiple({-5, 5}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({-2, -3, 5}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({-7, 2}), 1);
    EXPECT_EQ(s2.nSubsetsWithMultiple({-1, 1}), 1);
}

TEST_F(SubsetSumsMultipleTest, NoValidSubsets) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({1}), 0);
    EXPECT_EQ(s5.nSubsetsWithMultiple({1, 2}), 0);
    EXPECT_EQ(s5.nSubsetsWithMultiple({1, 3, 8}), 0);
    EXPECT_EQ(s5.nSubsetsWithMultiple({2, 2, 2}), 0);
}

TEST_F(SubsetSumsMultipleTest, AllElementsAreMultiples) {
    EXPECT_EQ(s5.nSubsetsWithMultiple({5}), 1);
    EXPECT_EQ(s5.nSubsetsWithMultiple({5, 5}), 3);
    EXPECT_EQ(s5.nSubsetsWithMultiple({5, 10, 15}), 6);
    EXPECT_EQ(s3.nSubsetsWithMultiple({3, 6}), 3);
}

TEST_F(SubsetSumsMultipleTest, BruteForceExhaustiveSmallInputs) {
    for (const int k : {2, 3, 5, 7}) {
        Solution s(k);

        std::function<void(std::vector<int>&, int)> enumerate =
            [&](std::vector<int>& cur, int pos) {
                if (pos == 5) {
                    EXPECT_EQ(s.nSubsetsWithMultiple(cur),
                              countSubarraysBruteForce(cur, k));
                    return;
                }

                for (int val = -3; val <= 5; ++val) {
                    cur.push_back(val);
                    enumerate(cur, pos + 1);
                    cur.pop_back();
                }
            };

        std::vector<int> cur;
        enumerate(cur, 0);
    }
}