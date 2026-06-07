# C++ Interview Harness

A small CMake + GoogleTest harness for LeetCode and interview practice.

Each problem lives as a standalone `tests/*_test.cpp` file. Put the `Solution`
class and the GoogleTest cases in the same file, usually inside a namespace
matching the problem name.

## Layout

```text
cpp-interview-harness/
  CMakeLists.txt
  include/
    leetcode.hpp
  tests/
    destination_city_test.cpp
    two_sum_test.cpp
```

## Build

From this directory:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The first configure downloads GoogleTest automatically.

## Run All Tests

```sh
ctest --test-dir build --output-on-failure
```

Or run the GoogleTest binary directly:

```sh
./build/problem_tests
```

## Run One Problem

List tests:

```sh
./build/problem_tests --gtest_list_tests
```

Run only Destination City:

```sh
./build/problem_tests --gtest_filter='DestinationCity.*'
```

Run only Two Sum:

```sh
./build/problem_tests --gtest_filter='TwoSum.*'
```

## Add A New Problem

Create a new file:

```sh
touch tests/my_problem_test.cpp
```

Use this pattern:

```cpp
#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace my_problem {

class Solution {
public:
    int solve(vector<int>& nums) {
        return static_cast<int>(nums.size());
    }
};

}  // namespace my_problem

TEST(MyProblem, ExampleCases) {
    my_problem::Solution solution;

    vector<int> nums{1, 2, 3};
    EXPECT_EQ(solution.solve(nums), 3);
}
```

Then rebuild and run:

```sh
cmake --build build
ctest --test-dir build --output-on-failure
```

## Useful Flags

Debug build:

```sh
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build-debug
ctest --test-dir build-debug --output-on-failure
```

Run with sanitizers on Clang or GCC:

```sh
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer'
cmake --build build-asan
./build-asan/problem_tests
```
