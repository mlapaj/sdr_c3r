# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Multimedia)

# the compile lines.
include_directories(${Qt5Multimedia_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Multimedia_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Multimedia_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(IO IqDataReader.cxx AudioOutput.cxx )
target_link_libraries (IO Qt5::Widgets Qt5::Multimedia) 
