# Main build target (executable)
add_executable(App
        pch.h
        main.cpp
)

# Configure target
add_default_configurations(App app)

# Add current dir to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use precompiled header
target_precompile_headers(App PRIVATE pch.h)

# Link with object formatter lib
target_link_libraries(App PRIVATE Formatter)