cmake_minimum_required (VERSION 2.6)
project (sdr_c3r)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


add_subdirectory(DSP)
add_subdirectory(IO)

# find google test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# for main program
add_executable(sdr_c3r main.cxx)
target_link_libraries(sdr_c3r DSP IO log4cplus)

# for testing
add_executable(tests tests.cxx)
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} pthread log4cplus)

