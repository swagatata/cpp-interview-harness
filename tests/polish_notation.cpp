#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace polish_notation {

class Solution {
public:
    int evaluate(const string& expression) {
        // TODO: implement
        for (auto& token : parse_tokens(expression)) {
            if (isnumber(token)) {
                st.push()
            }
            switch (token)
            {
            case '*':
                /* code */
                break;    
            case "+":
                break;        
            default:
                break;
            }
        }
        return 0;
    }
private:
    iterator<string> parse_tokens(const string& expressions) {
        // TODO
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
