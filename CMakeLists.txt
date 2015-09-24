cmake_minimum_required (VERSION 2.6)
project (sdr_c3r)



enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(sdr_c3r main.cxx)


add_executable(tests tests.cxx)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)

