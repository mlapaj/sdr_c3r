cmake_minimum_required (VERSION 2.6)
project (sdr_c3r)


add_subdirectory(DSP)

# find google test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# for main program
add_executable(sdr_c3r main.cxx)
target_link_libraries(sdr_c3r DSP)

# for testing
add_executable(tests tests.cxx)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread)

