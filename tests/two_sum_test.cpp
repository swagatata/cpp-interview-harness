#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace two_sum {

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            const int need = target - nums[i];
            if (seen.contains(need)) {
                return {seen[need], i};
            }
            seen[nums[i]] = i;
        }

        return {};
    }
};

}  // namespace two_sum

TEST(TwoSum, LeetCodeExamples) {
    two_sum::Solution solution;

    vector<int> nums1{2, 7, 11, 15};
    EXPECT_EQ(solution.twoSum(nums1, 9), (vector<int>{0, 1}));

    vector<int> nums2{3, 2, 4};
    EXPECT_EQ(solution.twoSum(nums2, 6), (vector<int>{1, 2}));

    vector<int> nums3{3, 3};
    EXPECT_EQ(solution.twoSum(nums3, 6), (vector<int>{0, 1}));
}
