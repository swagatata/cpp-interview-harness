#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace destination_city {

class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_set<string> outgoing;

        for (const auto& path : paths) {
            outgoing.insert(path[0]);
        }

        for (const auto& path : paths) {
            if (!outgoing.contains(path[1])) {
                return path[1];
            }
        }

        return "";
    }
};

}  // namespace destination_city

TEST(DestinationCity, LeetCodeExamples) {
    destination_city::Solution solution;

    vector<vector<string>> paths1{
        {"London", "New York"},
        {"New York", "Lima"},
        {"Lima", "Sao Paulo"},
    };
    EXPECT_EQ(solution.destCity(paths1), "Sao Paulo");

    vector<vector<string>> paths2{
        {"B", "C"},
        {"D", "B"},
        {"C", "A"},
    };
    EXPECT_EQ(solution.destCity(paths2), "A");

    vector<vector<string>> paths3{{"A", "Z"}};
    EXPECT_EQ(solution.destCity(paths3), "Z");
}
