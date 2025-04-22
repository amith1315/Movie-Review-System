cmake_minimum_required(VERSION 3.10)
project(MovieRatingSystem)

set(CMAKE_CXX_STANDARD 17)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(
    src
    src/controller
    src/model
    src/view
    ${SQLite3_INCLUDE_DIRS}
)

# Gather all source files
file(GLOB_RECURSE SOURCES
    src/main.cpp
    src/controller/*.cpp
    src/model/*.cpp
    src/view/*.cpp
)

# Executable
add_executable(MovieRatingSystem ${SOURCES})

# Link SQLite3
target_link_libraries(MovieRatingSystem ${SQLite3_LIBRARIES})

