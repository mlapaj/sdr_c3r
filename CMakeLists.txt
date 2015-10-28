cmake_minimum_required (VERSION 2.6)
project (sdr_c3r)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pg") # -g
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -pg") # -g
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()



# Find the QtWidgets library
find_package(Qt5Widgets)

# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# find google test
# add_definitions(-DNDEBUG=1) remove if debug not needed
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
target_link_libraries(sdr_c3r IO MISC GUI RADIO DSP Qt5::Widgets ${GLOG_LIBRARIES})

# for testing
add_executable(tests tests.cxx)
target_link_libraries(tests DSP IO MISC ${GTEST_BOTH_LIBRARIES} pthread)

file(COPY test_data DESTINATION .)
