#include <gtest/gtest.h>

class Solution {
public:
    bool isValidPalindrome(const std::string s) {
        if (s.empty())
            return true;

        size_t l = 0, r = s.size() - 1;
        while (l < r) {
            while (l < r && !std::isalnum(s[l])) l++;
            while (l < r && !std::isalnum(s[r])) r--;

            if (std::tolower(s[l]) != std::tolower(s[r]))
                return false;

            if (l >= r)
                break;

            l++;            
            r--;
        }

        return true;
    }
};

TEST(ValidPalindrome, Empty) {
    Solution s;
    EXPECT_TRUE(s.isValidPalindrome(""));
    EXPECT_TRUE(s.isValidPalindrome(" "));
}

TEST(ValidPalindrome, SimpleShort) {
    Solution s;
    EXPECT_FALSE(s.isValidPalindrome("ab"));
    EXPECT_TRUE(s.isValidPalindrome("aba"));
    EXPECT_TRUE(s.isValidPalindrome("abba"));
}

TEST(ValidPalindrome, IgnoreCase) {
    Solution s;
    EXPECT_FALSE(s.isValidPalindrome("aB"));
    EXPECT_TRUE(s.isValidPalindrome("aBa"));
    EXPECT_TRUE(s.isValidPalindrome("aBA"));
    EXPECT_TRUE(s.isValidPalindrome("abBA"));
}

TEST(ValidPalindrome, IgnorePunctuation) {
    Solution s;
    EXPECT_TRUE(s.isValidPalindrome("a ."));
    EXPECT_FALSE(s.isValidPalindrome("aB "));
    EXPECT_FALSE(s.isValidPalindrome("a B "));
    EXPECT_TRUE(s.isValidPalindrome("a,Ba"));
    EXPECT_TRUE(s.isValidPalindrome("aB; A"));
    EXPECT_TRUE(s.isValidPalindrome("       , abBA."));
}

TEST(ValidPalindrome, TrailingPunctuation) {
    Solution s;
    EXPECT_TRUE(s.isValidPalindrome("a,"));
    EXPECT_TRUE(s.isValidPalindrome("a."));
    EXPECT_TRUE(s.isValidPalindrome("aba;"));
    EXPECT_TRUE(s.isValidPalindrome("121,"));
    EXPECT_TRUE(s.isValidPalindrome("racecar."));
}

TEST(ValidPalindrome, LookAlikes) {
    Solution s;
    EXPECT_TRUE(s.isValidPalindrome("0O0"));
    EXPECT_FALSE(s.isValidPalindrome("O0O0"));
    EXPECT_TRUE(s.isValidPalindrome("O0O"));
    EXPECT_TRUE(s.isValidPalindrome("8:8"));
}

TEST(ValidPalindrome, ClassicPhrases) {
    Solution s;
    EXPECT_TRUE(s.isValidPalindrome("A man, a plan, a canal: Panama"));
    EXPECT_TRUE(s.isValidPalindrome("Was it a car or a cat I saw?"));
    EXPECT_FALSE(s.isValidPalindrome("Not a palindrome"));
}