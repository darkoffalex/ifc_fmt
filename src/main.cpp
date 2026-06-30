#include "pch.h"
#include "utils.h"

/**
 * Entry point
 * @param argc Argument count
 * @param argv Arguments
 * @return Exit code (0 = success)
 */
int main(const int argc, char* argv[])
{
    try
    {
        // Ensure arguments
        if (argc < 3){
            throw std::runtime_error("Usage: " + std::string(argv[0]) + " <input_file.ifc> <output_file.ifc>");
        }

        // Open files (read & write)
        std::ifstream input_file;
        input_file.exceptions(std::ios::failbit | std::ios::badbit);
        input_file.open(argv[1], std::ios::in);

        std::ofstream output_file;
        output_file.exceptions(std::ios::failbit | std::ios::badbit);
        output_file.open(argv[2], std::ios::out | std::ios::trunc);

        // Read input file contents
        const auto file_contents = utils::read_to_string(input_file);
        // Get wanted data slice
        auto data_slice = utils::str_slice(file_contents, "DATA;", "ENDSEC;");

        // Debug (temporary)
        std::cout << data_slice << std::endl;

        // TODO: Implement formatting

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
