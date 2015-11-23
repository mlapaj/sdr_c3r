cmake_minimum_required (VERSION 2.6)
project (sdr_c3r)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)


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


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fopenmp -g") # -g -pg


# find google test
# add_definitions(-DNDEBUG=1) # remove if debug not needed
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
# find google test
find_package (GLog REQUIRED)

add_subdirectory(DSP)
add_subdirectory(IO)
add_subdirectory(MISC)
add_subdirectory(RADIO)
add_subdirectory(GUI)


# for main program
add_executable(sdr_c3r main.cxx)
target_link_libraries(sdr_c3r IO MISC GUI RADIO DSP ${GLOG_LIBRARIES})

# for testing
add_executable(tests tests.cxx)
target_link_libraries(tests DSP IO MISC ${GTEST_BOTH_LIBRARIES} pthread)

file(COPY test_data DESTINATION .)
