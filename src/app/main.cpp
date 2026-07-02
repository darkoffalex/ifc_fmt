#include "pch.h"
#include <formatter/formatter.h>

/**
 * Entry point
 * @param argc Argument count (3 required)
 * @param argv File paths arguments
 * @return Exit code
 */
int main(const int argc, char* argv[])
{
    try
    {
        // Ensure arguments
        if (argc < 3){
            throw std::runtime_error("Usage: " + std::string(argv[0]) + " <input_file.ifc> <output_file.ifc>");
        }

        // Format file
        fmt::format_file(argv[1], argv[2]);
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << "Can't open file: " + std::string(e.what()) << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}