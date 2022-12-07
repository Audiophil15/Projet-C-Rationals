cmake_minimum_required(VERSION 3.10)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(testRationals unit_test.cpp)
target_compile_features(testRationals PUBLIC cxx_std_20)
target_include_directories(testRationals PUBLIC ${INCLUDE_DIRECTORIES}/rationals)
target_link_libraries(testRationals ${GTEST_LIBRARIES} pthread)
