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
        simple.cpp
)

# Link with formatter lib & testing framework
target_link_libraries(Tests PRIVATE
        Formatter
        Catch2::Catch2WithMain)

# Enable testing
include(CTest)
include(Catch)
catch_discover_tests(Tests)