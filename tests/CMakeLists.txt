# Add Catch2
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Auto-test executable sources
add_executable(Tests
        pch.h
        test_simple.cpp
        test_files.cpp
)

# Configure target
add_default_configurations(Tests tests)

# Add current dir to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use precompiled header
target_precompile_headers(Tests PRIVATE pch.h)

# Absolute path to project root folder
target_compile_definitions(Tests PRIVATE
        PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
)

# Link with formatter lib & testing framework
target_link_libraries(Tests PRIVATE
        Formatter
        Catch2::Catch2WithMain)

# Enable testing
include(CTest)
include(Catch)
catch_discover_tests(Tests)