#include "leetcode.hpp"

#include <sstream>

#include <gtest/gtest.h>

namespace polish_notation {

class Solution {
public:
    int evaluate(const string& expression) {
        stack<int> values;

        for (const auto& token : parse_tokens(expression)) {
            if (is_operator(token)) {
                const int rhs = values.top();
                values.pop();
                const int lhs = values.top();
                values.pop();

                values.push(apply_operator(lhs, rhs, token));
            } else {
                values.push(stoi(token));
            }
        }

        return values.top();
    }
private:
    vector<string> parse_tokens(const string& expression) {
        istringstream stream(expression);
        vector<string> tokens;
        string token;

        while (stream >> token) {
            tokens.push_back(token);
        }

        return tokens;
    }

    bool is_operator(const string& token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    int apply_operator(int lhs, int rhs, const string& op) {
        if (op == "+") {
            return lhs + rhs;
        }
        if (op == "-") {
            return lhs - rhs;
        }
        if (op == "*") {
            return lhs * rhs;
        }
        return lhs / rhs;
    }
};

struct TestCase {
    string expression;
    int expected;
};

class PolishNotationTest : public testing::TestWithParam<TestCase> {};

TEST_P(PolishNotationTest, EvaluatesExpression) {
    polish_notation::Solution solution;

    const auto& param = GetParam();
    EXPECT_EQ(solution.evaluate(param.expression), param.expected);
}

INSTANTIATE_TEST_SUITE_P(
    Examples,
    PolishNotationTest,
    testing::Values(
        TestCase{"2 1 + 3 *", 9},
        TestCase{"4 13 5 / +", 6},
        TestCase{"10 6 9 3 + -11 * / * 17 + 5 +", 22}));

}  // namespace polish_notation
