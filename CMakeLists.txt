# CMake version
cmake_minimum_required(VERSION 3.15...3.29)

# Enable runtime type management for MSVC
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

# Project name
project(IFC_Formatter)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(BEFORE include)

# Binary directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)

# Use static runtime linking
option(STATIC_RUNTIME "Use static runtime linking" OFF)

# Architecture detection
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_NAME "x64")
    set(ARCH "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(ARCH_NAME "x86")
    set(ARCH "32")
else()
    message(FATAL_ERROR "Unsupported architecture. Size of pointer is: ${CMAKE_SIZEOF_VOID_P}")
endif()

# Helper function to configure build targets
# Also adds additional flags to targets, can be called from sub-projects
function(add_default_configurations TARGET_NAME TARGET_BIN_NAME)
    # Output file name
    set_property(TARGET ${TARGET_NAME} PROPERTY OUTPUT_NAME "${TARGET_BIN_NAME}_${ARCH_NAME}")

    # For MSVC compilers
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_definitions(${TARGET_NAME} PRIVATE "-DNOMINMAX")
        target_compile_options(${TARGET_NAME} PRIVATE /W3 /permissive- /fp:fast)
        if(STATIC_RUNTIME)
            set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
        else()
            set_property(TARGET ${TARGET_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>")
        endif()

    # For GNU/MinGW/Clang compilers
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -ffast-math -Wno-unknown-pragmas)
        if(STATIC_RUNTIME)
            target_link_options(${TARGET_NAME} PRIVATE
                    $<$<PLATFORM_ID:Windows>:-static>
                    $<$<NOT:$<PLATFORM_ID:Windows>>:-static-libgcc -static-libstdc++>
            )
        endif()

    # Other compilers (unsupported)
    else()
        message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()

# Add sub-projects
add_subdirectory(src/formatter)
add_subdirectory(src/app)
add_subdirectory(src/tests)