#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace course_schedule {

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> matrix(numCourses);
        for (auto preq : prerequisites) {
            matrix[preq[0]].push_back(preq[1]);
        }
        // cout << "printing matrix" << endl;
        // for (auto m : matrix) {
        //     for (auto e : m) {
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }

        std::stack<int, std::vector<int>> st;
        std::vector<int> visited(numCourses, 0);
        for (size_t i = 0; i < matrix.size(); i++) {
            if (visited[i] == 2) {
                continue;
            } else if (visited[i] == 1) {
                return false;
            }
            st.emplace(i);      
            while (!st.empty()) {
                auto node = st.top();
                if (visited[node] == 0) {
                    visited[node] = 1;
                    for (int preq : matrix[node]) {
                        if (visited[preq] == 1) {
                            return false;
                        }
                        if (visited[preq] == 0) {
                            st.emplace(preq);
                        }
                    }
                } else {
                    visited[node] = 2;
                    st.pop();
                }
            }
        }

        return true;
    }
};

struct TestCase {
    int numCourses;
    vector<vector<int>> prerequisites;
    bool expected;
};

class CourseScheduleTest : public testing::TestWithParam<TestCase> {};

TEST_P(CourseScheduleTest, CanFinish) {
    Solution solution;
    auto prerequisites = GetParam().prerequisites;
    EXPECT_EQ(solution.canFinish(GetParam().numCourses, prerequisites), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    CourseScheduleTest,
    testing::Values(
        // LeetCode examples
        TestCase{2, {{1, 0}}, true},
        TestCase{2, {{1, 0}, {0, 1}}, false},

        // No prerequisites
        TestCase{1, {}, true},
        TestCase{5, {}, true},

        // Simple chains
        TestCase{3, {{1, 0}, {2, 1}}, true},
        TestCase{4, {{1, 0}, {2, 1}, {3, 2}}, true},

        // Diamond (fork and join)
        TestCase{4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true},

        // Star: every course depends on course 0
        TestCase{5, {{1, 0}, {2, 0}, {3, 0}, {4, 0}}, true},

        // Multiple prerequisites for one course
        TestCase{4, {{1, 0}, {1, 2}, {3, 1}}, true},

        // Tree-shaped dependencies
        TestCase{3, {{0, 1}, {0, 2}, {1, 2}}, true},
        TestCase{5, {{1, 0}, {2, 0}, {3, 1}, {3, 2}, {4, 3}}, true},

        // Two-node cycle
        TestCase{2, {{0, 1}, {1, 0}}, false},

        // Three-node cycle
        TestCase{3, {{0, 1}, {1, 2}, {2, 0}}, false},

        // Four-node cycle
        TestCase{4, {{1, 0}, {2, 1}, {3, 2}, {0, 3}}, false},

        // Cycle in one component among otherwise valid courses
        TestCase{4, {{1, 0}, {3, 2}, {0, 3}, {3, 0}}, false},

        // Independent acyclic components
        TestCase{4, {{1, 0}, {3, 2}}, true},

        // Longer acyclic path with side branches
        TestCase{6, {{1, 0}, {2, 1}, {3, 2}, {4, 2}, {5, 4}}, true},

        // Cycle not involving every course
        TestCase{4, {{1, 0}, {2, 1}, {1, 2}, {3, 2}}, false},

        // Interleaved dependencies across seven courses
        TestCase{7, {{1, 0}, {0, 3}, {0, 2}, {3, 2}, {2, 5}, {4, 5}, {5, 6}, {2, 4}}, true}
    ));

}  // namespace course_schedule
