# Build target (obj-library)
add_library(Formatter OBJECT
        pch.h
        formatter.cpp
)

# Configure target
add_default_configurations(Formatter formatter)

# Add current dir to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Use precompiled header
target_precompile_headers(Formatter PRIVATE pch.h)