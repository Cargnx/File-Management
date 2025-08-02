cmake_minimum_required(VERSION 3.31)
project(File_Management)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find all .cpp files inside src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Debug: print found sources
message(STATUS "Source files found: ${SOURCES}")

# Add the executable
add_executable(File_Management ${SOURCES})
