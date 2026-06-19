cmake_minimum_required(VERSION 3.20)

project(cpp_interview_harness LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE PROBLEM_TESTS CONFIGURE_DEPENDS tests/*.cpp)

set(EXCLUDED_PROBLEM_TESTS "" CACHE STRING "Semicolon-separated test source files to exclude")
foreach(EXCLUDED_TEST IN LISTS EXCLUDED_PROBLEM_TESTS)
  if(IS_ABSOLUTE "${EXCLUDED_TEST}")
    set(EXCLUDED_TEST_PATH "${EXCLUDED_TEST}")
  else()
    cmake_path(ABSOLUTE_PATH EXCLUDED_TEST BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" NORMALIZE OUTPUT_VARIABLE EXCLUDED_TEST_PATH)
  endif()
  list(REMOVE_ITEM PROBLEM_TESTS "${EXCLUDED_TEST_PATH}")
endforeach()

add_executable(problem_tests ${PROBLEM_TESTS})
target_include_directories(problem_tests PRIVATE include)
target_link_libraries(problem_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(problem_tests)
