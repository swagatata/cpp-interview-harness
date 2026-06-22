#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace rotting_oranges {

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty())
            return 0;

        // add all rotten to queue
        size_t m = grid.size(), n = grid[0].size();
        std::queue<pair<size_t, size_t>> q;
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.emplace(i, j);
                    // std::cout << "Adding to Q: " << i << " " << j << std::endl;
                }
            }
        }

        int runs = 0, qsize = 0;
        while(!q.empty()) {
            qsize = q.size();     
            for (size_t i = 0; i < qsize; ++i) {
                auto [x, y] = q.front(); q.pop();
                if (x > 0 && grid[x-1][y] == 1) {
                    q.emplace(x-1, y);
                    grid[x-1][y] = 2;
                }
                if (y > 0 && grid[x][y-1] == 1) {
                    q.emplace(x, y-1);
                    grid[x][y-1] = 2;
                }
                if (y < n - 1 && grid[x][y+1] == 1) {
                    q.emplace(x, y + 1);
                    grid[x][y+1] = 2;
                }
                if (x < m - 1 && grid[x+1][y] == 1) {
                    q.emplace(x+1, y);
                    grid[x+1][y] = 2;
                }
            }
            runs++;
        }


        // start bfs for all of them. 


        // count number of runs until queue becomes empty

        // LeetCode 994: implement here.
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }        
        if (runs > 0)
            return runs - 1;
        return 0;
    }
};

struct TestCase {
    vector<vector<int>> grid;
    int expected;
};

class OrangesRottingTest : public testing::TestWithParam<TestCase> {};

TEST_P(OrangesRottingTest, RottingOranges) {
    Solution solution;
    auto grid = GetParam().grid;
    EXPECT_EQ(solution.orangesRotting(grid), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    OrangesRottingTest,
    testing::Values(
        // LeetCode examples
        TestCase{{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}, 4},
        TestCase{{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}, -1},
        TestCase{{{0, 2}}, 0},

        // // Single cell
        TestCase{{{0}}, 0},
        TestCase{{{1}}, -1},
        TestCase{{{2}}, 0},

        // No work needed
        TestCase{{{0, 0}, {0, 0}}, 0},
        TestCase{{{2, 0, 2}, {0, 0, 0}}, 0},

        // // No rotten orange to spread from
        TestCase{{{1, 1}, {1, 1}}, -1},

        // // Fresh orange unreachable from any rotten orange
        TestCase{{{1, 0, 2}}, -1},
        TestCase{{{2, 1, 0, 1, 1}}, -1},
        TestCase{{{2, 0, 0}, {0, 1, 0}, {0, 0, 0}}, -1},

        // // Linear spread
        TestCase{{{1, 1, 2, 1, 1}}, 2},
        TestCase{{{2, 1, 1, 1}}, 3},

        // // Multiple rotten sources
        TestCase{{{2, 1, 2}, {1, 1, 1}, {1, 1, 1}}, 3},

        // // Rotten orange in the center
        TestCase{{{1, 1, 1}, {1, 2, 1}, {1, 1, 1}}, 2},

        // // One row, rotten at an end
        TestCase{{{2, 1, 1, 1, 1}}, 4}
    ));

}  // namespace rotting_oranges
