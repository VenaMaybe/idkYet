cmake_minimum_required(VERSION 3.10)
project(Honors LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set only for debugging
set(CMAKE_BUILD_TYPE Debug)

# Paths to RayLib
include_directories(../raylib-5.5_linux_amd64/include)
link_directories(../raylib-5.5_linux_amd64/lib)

# Automatically collect all source and header files
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h")

# Add an executable target
add_executable(idkYet ${SRC_FILES} ${HEADER_FILES})

# If you have additional include directories
target_include_directories(idkYet PRIVATE include)

# Link RayLib to the executable
target_link_libraries(idkYet PRIVATE raylib)
