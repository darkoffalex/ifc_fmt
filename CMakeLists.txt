# Cmake version
cmake_minimum_required(VERSION 3.15...3.29)

# Project name
project(ifc_fmt)

# C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Binary output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)

# Include directories
include_directories(BEFORE include)

# Sources
add_executable(ifc_fmt
        src/pch.h
        src/main.cpp
)

# Pre-compiled headers
target_precompile_headers(ifc_fmt PRIVATE src/pch.h)
