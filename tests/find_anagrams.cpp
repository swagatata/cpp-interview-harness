#include <gtest/gtest.h>

class Solution {
public:
    Solution(std::string s) : d_s(s) {

    }

    bool matched(const std::array<int, 26>& a, const std::array<int, 26>& b) {
        for (int i = 0; i < 26; ++i)
            if (a[i] != b[i])
                return false;

        return true;
    }

    std::vector<int> findAnagrams(std::string p) {
        if (p.empty())
            return {};

        if (p.size() > d_s.size())
            return {};

        std::array<int, 26> pCounts; pCounts.fill(0);
        std::array<int, 26> sCounts; sCounts.fill(0);

        int n = p.size();
        for (int i = 0; i < n; ++i) {
            pCounts[p[i] - 'a']++;
            sCounts[d_s[i] - 'a']++;
        }
        
        std::vector<int> total;
        bool ismatched = false;
        if (matched(pCounts, sCounts)) {
            total.push_back(0);
            ismatched = true;
        }

        int j = n;        
        while (j < d_s.size()) {
            if (ismatched){
                if (d_s[j - n] == d_s[j]) {
                    total.push_back(j + 1 - n);
                    j++;
                    continue;
                }        
            }

            if (d_s[j] == d_s[j - n]) {
                j++;
                continue;
            }

            sCounts[d_s[j - n] - 'a']--;
            sCounts[d_s[j] - 'a']++;
            ismatched = matched(sCounts, pCounts);
            
            if (ismatched)
                total.push_back(j + 1 - n);

            j++;
        }

        return total;
    }

private:
    std::string d_s;
};

TEST(FindAnagrams, Empty) {
    Solution s("");
    EXPECT_EQ(s.findAnagrams(""), (std::vector<int>{}));
}

TEST(FindAnagrams, Single) {
    Solution s("abc");
    EXPECT_EQ(s.findAnagrams("a"), (std::vector<int>{0}));
    EXPECT_EQ(s.findAnagrams("b"), (std::vector<int>{1}));
    EXPECT_EQ(s.findAnagrams("c"), (std::vector<int>{2}));
}

TEST(FindAnagrams, Problem) {
    Solution scbaebabacd("cbaebabacd");
    EXPECT_EQ(scbaebabacd.findAnagrams("abc"), (std::vector<int>{0, 6}));
}