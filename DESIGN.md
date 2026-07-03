# IFC-formatter

## Build Instructions

Requirements:
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.15 or higher

**1. Generate build files:**
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

**2. Compile project:**
```bash
cmake --build build --config Release
```

**3. Run:**
```bash
# Windows
bin\Release\app_x64.exe <input.ifc> <output.ifc>

# Linux/macOS
./bin/Release/app_x64 <input.ifc> <output.ifc>
```
>You also can build the project with an IDE that supports CMake (Visual Studio, CLion, etc.). Project was developed and built with **CLion 2026.1.3**, **CMake 3.28.3**, **GNU C++ Compiler 13.3.0**.

## Run tests

There are two ways to run tests:
- Run command `ctest -C Release --output-on-failure` after building the project (make soure you are in the `build` directory before running this command)
- Run the compiled `tests_x64` (or `tests_x86`) binary file.

## Approach at high level
The project is divided into three parts: 
- Static object library called `Formatter` with business logic
- Console application called `App` (only argument parsing and logic invocation), 
- Executable file called `Tests` for unit testing.

### Parsing approach 
Regular expressions (regex) were avoided because they struggle with nested parentheses and escaped quotes. Instead, a simple state machine was implemented to process the DATA section character by character. It tracks the parsing state using a few variables (such as an in_string flag for string literals and a paren_depth counter for parentheses nesting) to safely assemble the properly formatted text.

### Memory handling 
The entire file is read into memory at once. To prevent unnecessary memory allocations, std::string_view is used to slice the content into logical parts (Header, DATA, and Footer) without copying the underlying strings.

## Assumptions & limitations
1. **File size:**
   The input IFC file size does not exceed the available RAM. The program reads the entire file into std::string.

2. **Encoding:**
   The file is saved in ASCII or a compatible encoding (UTF-8).

3. **File structure:**
   The file has exactly one DATA; section.

## What I would do next with more time
1. **Stream-based processing:**
   Transition from loading the entire file into RAM to a streaming or chunk-based reading approach. Since real-world files can be several gigabytes in size, processing the file sequentially using I/O streams would make the tool highly scalable regardless of available memory.

2. **Detailed error diagnostics:**
   Enhance the state machine to track line and column numbers during parsing. If a syntax error occurs (e.g., an unclosed string literal or an unmatched parenthesis), the tool would report the exact location of the anomaly, significantly improving the developer experience.

3. **In-place formatting and batch processing:**
   Add support for in-place modification to overwrite the original file without requiring an explicit output path. Additionally, implement batch processing to format entire directories of IFC files at once.