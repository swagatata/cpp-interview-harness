#include "leetcode.hpp"

#include <chrono>

#include <gtest/gtest.h>

namespace raining_cities {

class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        const int n = static_cast<int>(rains.size());
        vector<int> ans(n, -1);
        unordered_map<int, int> lastRain;
        lastRain.reserve(n);
        set<int> dryDays;

        for (int i = 0; i < n; ++i) {
            const int lake = rains[i];
            if (lake == 0) {
                dryDays.insert(i);
                ans[i] = 1;
                continue;
            }

            if (const auto prev = lastRain.find(lake); prev != lastRain.end()) {
                auto it = dryDays.upper_bound(prev->second);
                if (it == dryDays.end()) {
                    return {};
                }
                ans[*it] = lake;
                dryDays.erase(it);
            }

            lastRain[lake] = i;
        }

        return ans;
    }
};

class SetReferenceSolution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        unordered_map<int, int> lastRain;
        set<int> dryDays;
        vector<int> ans(rains.size(), -1);

        for (int i = 0; i < static_cast<int>(rains.size()); ++i) {
            const int lake = rains[i];
            if (lake == 0) {
                dryDays.insert(i);
                continue;
            }

            if (const auto prev = lastRain.find(lake); prev != lastRain.end()) {
                auto it = dryDays.upper_bound(prev->second);
                if (it == dryDays.end()) {
                    return {};
                }
                ans[*it] = lake;
                dryDays.erase(it);
            }

            lastRain[lake] = i;
        }

        for (const int day : dryDays) {
            ans[day] = 1;
        }

        return ans;
    }
};

bool IsValidSchedule(const vector<int>& rains, const vector<int>& ans) {
    if (ans.empty()) {
        return true;
    }
    if (ans.size() != rains.size()) {
        return false;
    }

    unordered_set<int> fullLakes;
    for (int i = 0; i < static_cast<int>(rains.size()); ++i) {
        if (rains[i] == 0) {
            if (ans[i] <= 0) {
                return false;
            }
            fullLakes.erase(ans[i]);
            continue;
        }

        if (ans[i] != -1 || fullLakes.contains(rains[i])) {
            return false;
        }
        fullLakes.insert(rains[i]);
    }

    return true;
}

vector<int> MakeReplayWorkload(int lakeCount) {
    vector<int> rains;
    rains.reserve(lakeCount * 3);

    for (int lake = 1; lake <= lakeCount; ++lake) {
        rains.push_back(lake);
    }
    for (int i = 0; i < lakeCount; ++i) {
        rains.push_back(0);
    }
    for (int lake = 1; lake <= lakeCount; ++lake) {
        rains.push_back(lake);
    }

    return rains;
}

template <typename Solver>
long long BenchmarkMillis(Solver& solver, const vector<int>& rains, int repetitions) {
    const auto start = chrono::steady_clock::now();
    for (int i = 0; i < repetitions; ++i) {
        auto input = rains;
        auto ans = solver.avoidFlood(input);
        EXPECT_TRUE(IsValidSchedule(input, ans));
    }
    const auto end = chrono::steady_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

struct TestCase {
    vector<int> rains;
    vector<int> expected;
};

class AvoidFloodTest : public testing::TestWithParam<TestCase> {};

TEST_P(AvoidFloodTest, AvoidsFlood) {
    raining_cities::Solution solution;

    auto rains = GetParam().rains;
    EXPECT_EQ(solution.avoidFlood(rains), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Examples,
    AvoidFloodTest,
    testing::Values(
        TestCase{{1, 2, 3, 4}, {-1, -1, -1, -1}},
        TestCase{{1, 2, 0, 0, 2, 1}, {-1, -1, 2, 1, -1, -1}},
        TestCase{{1, 2, 0, 1, 2}, {}},
        TestCase{{69, 0, 0, 0, 69}, {-1, 69, 1, 1, -1}},
        TestCase{{0, 1, 1}, {}}));

TEST(AvoidFloodPerformanceTest, DISABLED_BenchmarkReplayWorkload) {
    auto rains = MakeReplayWorkload(10'000);
    Solution optimized;
    SetReferenceSolution reference;

    const long long optimizedMs = BenchmarkMillis(optimized, rains, 3);
    const long long referenceMs = BenchmarkMillis(reference, rains, 3);

    cout << "current solution: " << optimizedMs << " ms\n";
    cout << "set reference: " << referenceMs << " ms\n";
}

}  // namespace raining_cities
