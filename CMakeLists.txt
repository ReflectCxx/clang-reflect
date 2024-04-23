cmake_minimum_required(VERSION 3.0)

project(clang-reflect)

set (CMAKE_CXX_STANDARD 20)

# Set LLVM_SRC and LLVM_BUILD variables from command line
if(NOT LLVM_SRC)
    message(FATAL_ERROR "LLVM_SRC not provided. Please specify LLVM source directory.")
endif()

if(NOT LLVM_BUILD)
    message(FATAL_ERROR "LLVM_BUILD not provided. Please specify LLVM build directory.")
endif()

# Set policy CMP0076 to NEW
cmake_policy(SET CMP0076 NEW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Add subdirectories
add_subdirectory(inc)
add_subdirectory(src)