#include "leetcode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace sort_desc {

void sortDesc(std::vector<int>& nums) {
    // std::sort(nums.begin(), nums.end(), [](int i, int j){
    //     return i > j;
    // });

    std::ranges::sort(nums, std::greater<int>{});
}

void sortAbsolute(std::vector<int>& nums) {
    std::sort(nums.begin(), nums.end(), [](int x, int y){
        return abs(x) < abs(y);
    });
}

std::vector<int> sortAbsoluteFunctional(std::vector<int>&& v) {
    std::sort(v.begin(), v.end(), [](int x, int y){
        return abs(x) < abs(y) || x < y;
    });
    return v;
}

}  // namespace sort_desc

TEST(SortDesc, SortsNumbersInDescendingOrder) {
    std::vector<int> nums{5, 1, 9, 3, 7};

    sort_desc::sortDesc(nums);

    EXPECT_EQ(nums, (std::vector<int>{9, 7, 5, 3, 1}));
}

TEST(SortDesc, HandlesDuplicatesAndNegativeNumbers) {
    std::vector<int> nums{4, -2, 4, 0, -7, 9, 9};

    sort_desc::sortDesc(nums);

    EXPECT_EQ(nums, (std::vector<int>{9, 9, 4, 4, 0, -2, -7}));
}

TEST(SortDesc, LeavesEmptyAndSingleElementVectorsValid) {
    std::vector<int> empty;
    std::vector<int> single{42};

    sort_desc::sortDesc(empty);
    sort_desc::sortDesc(single);

    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(single, (std::vector<int>{42}));
}

TEST(SortAbsolute, SortsNumbersByAbsoluteValue) {
    std::vector<int> nums{5, -2, 1, -4, 3};

    sort_desc::sortAbsolute(nums);

    EXPECT_EQ(nums, (std::vector<int>{1, -2, 3, -4, 5}));
}

TEST(SortAbsolute, HandlesZeroAndNegativeNumbers) {
    std::vector<int> nums{0, -5, -1, 2, -3};

    sort_desc::sortAbsolute(nums);

    EXPECT_EQ(nums, (std::vector<int>{0, -1, 2, -3, -5}));
}

TEST(SortAbsolute, LeavesEmptyAndSingleElementVectorsValid) {
    std::vector<int> empty;
    std::vector<int> single{-7};

    sort_desc::sortAbsolute(empty);
    sort_desc::sortAbsolute(single);

    EXPECT_TRUE(empty.empty());
    EXPECT_EQ(single, (std::vector<int>{-7}));
}
