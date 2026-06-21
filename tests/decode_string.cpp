#include <leetcode.hpp>

/**
 * Inputs:

s = "3[a2[c]]"
Output:

"accaccacc"



 */

class Solution {
    public:
        string decodeString(string s) {
            if (s.empty()) {
                return s;
            }

            string curr = "", temp;
            stack<int> st;
            stack<string> cst;
            size_t position = 0;

            while (position < s.size()) {
                size_t i = position;
                while (std::isalpha(s[position])) {
                    position++;
                }
                if (position != i) {
                    cst.push(s.substr(i, position - i));
                    // continue;
                }

                int num = 0;
                while (std::isdigit(s[position])) {
                    num *= 10;
                    num += (s[position] - '0');
                    position++;
                }
                if (num) {
                    st.push(num);
                    // continue;
                }
                switch (s[position]) {
                    case '[':
                        cst.push("[");
                        break;
                    case ']':
                        curr = "";
                        while (!cst.empty() && cst.top() != "[") {
                            curr.insert(0, cst.top());
                            cst.pop();
                        }
                        temp = "";
                        for (int i = 0; i < st.top(); ++i) {
                            temp.append(curr);
                        }
                        st.pop();
                        cst.pop();
                        cst.push(temp);
                        break;
                    default:
                        break;
                }
                position++;
            }

            curr = "";
            while (!cst.empty()) {
                curr.insert(0, cst.top());
                cst.pop();
            }
            return curr;
        }
    };

#include <gtest/gtest.h>

namespace decode_string {

struct TestCase {
    string input;
    string expected;
};

class DecodeStringTest : public testing::TestWithParam<TestCase> {};

TEST_P(DecodeStringTest, DecodesInput) {
    Solution solution;
    const auto& param = GetParam();
    EXPECT_EQ(solution.decodeString(param.input), param.expected);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    DecodeStringTest,
    testing::Values(
        TestCase{"", ""},
        TestCase{"abc", "abc"},
        TestCase{"3[a]", "aaa"},
        TestCase{"3[a]bc", "aaabc"},
        TestCase{"2[ab]", "abab"},
        TestCase{"10[a]", "aaaaaaaaaa"},
        TestCase{"3[a2[c]]", "accaccacc"},
        TestCase{"2[a2[b]]", "abbabb"},
        TestCase{"abc3[cd]xyz", "abccdcdcdxyz"},
        TestCase{"1[a]", "a"},
        TestCase{"2[3[a]]", "aaaaaa"},
        TestCase{"2[a]3[b]4[c]", "aabbbcccc"},
        TestCase{"2[a3[b4[c]]]", "abccccbccccbccccabccccbccccbcccc"},
        TestCase{"2[ab3[cd]ef4[gh]]", "abcdcdcdefghghghghabcdcdcdefghghghgh"},
        TestCase{"a1[b2[c]]d", "abccd"}
));

}  // namespace decode_string
