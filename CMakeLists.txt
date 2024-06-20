# CMakeLists.txt for the entire project
cmake_minimum_required(VERSION 3.20)
# Set the project name
project(clang-reflect)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add the subdirectories
add_subdirectory(clang-reflect)