#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace two_d_islands {

class Solution {
public:
    void traverse(vector<vector<char>>& grid, int x, int y) {
        std::stack<pair<int, int>, std::vector<pair<int, int>>> st;
        grid[x][y] = 'v';
        st.emplace(x, y);

        int m = grid.size();
        int n = grid[0].size();
        while (!st.empty()) {
            auto [i, j] = st.top(); st.pop();            
            // std::cout << "visiting " << i << ", " << j << std::endl;
            if (i > 0)
                if (grid[i-1][j] == '1') {
                    grid[i-1][j] = 'v';
                    st.emplace(i-1, j);
                }
                // traverse(grid, i-1, j);        
            if (j < (n - 1))
                if (grid[i][j+1] == '1') {
                    grid[i][j+1] = 'v';
                    st.emplace(i, j+1);
                }
                // traverse(grid, i, j+1);
            if (i < (m - 1))
                if (grid[i+1][j] == '1') {
                    grid[i+1][j] = 'v';
                    st.emplace(i+1, j);
                }
                // traverse(grid, i+1, j);
            if (j > 0)
                if (grid[i][j-1] == '1') {
                    grid[i][j-1] = 'v';
                    st.emplace(i, j-1);
                }
                // traverse(grid, i, j-1);                                       
        }
    }

    int numIslands(vector<vector<char>>& grid) {
        int total = 0;

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (grid[i][j] == '1') {
                    traverse(grid, i, j);
                    total++;
                }                                
            }
        }

        return total;
    }
};

}  // namespace two_d_islands

TEST(TwoDIslands, EmptyGrid) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid;

    EXPECT_EQ(solution.numIslands(grid), 0);
}

TEST(TwoDIslands, AllWater) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'0', '0', '0'},
        {'0', '0', '0'},
    };

    EXPECT_EQ(solution.numIslands(grid), 0);
}

TEST(TwoDIslands, AllLand) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '1', '1'},
        {'1', '1', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 1);
}

TEST(TwoDIslands, SingleCellLand) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{{'1'}};

    EXPECT_EQ(solution.numIslands(grid), 1);
}

TEST(TwoDIslands, SingleCellWater) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{{'0'}};

    EXPECT_EQ(solution.numIslands(grid), 0);
}

TEST(TwoDIslands, DiagonalLandsAreSeparate) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '0'},
        {'0', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 2);
}

TEST(TwoDIslands, SeparateIslandsInOneRow) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{{'1', '0', '1', '0', '1'}};

    EXPECT_EQ(solution.numIslands(grid), 3);
}

TEST(TwoDIslands, LeetCodeExampleOne) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'},
    };

    EXPECT_EQ(solution.numIslands(grid), 1);
}

TEST(TwoDIslands, LeetCodeExampleTwo) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 3);
}

TEST(TwoDIslands, LShapedIsland) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '0', '0'},
        {'1', '0', '0'},
        {'1', '1', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 1);
}

TEST(TwoDIslands, RingWithHole) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '1', '1', '1'},
        {'1', '0', '0', '1'},
        {'1', '0', '0', '1'},
        {'1', '1', '1', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 1);
}

TEST(TwoDIslands, Edges) {
    two_d_islands::Solution solution;
    vector<vector<char>> grid{
        {'1', '1', '1', '1'},
        {'0', '0', '0', '1'},
        {'1', '0', '0', '1'},
        {'1', '1', '1', '1'},
    };

    EXPECT_EQ(solution.numIslands(grid), 1);
}
