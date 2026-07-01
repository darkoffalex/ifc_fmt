#include "pch.h"
#include <formatter/formatter.h>
#include <formatter/utils.h>

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
        const auto file_contents = fmt::utils::str_read(input_file);

        // Get data section slice & format it
        auto data = fmt::utils::str_slice(file_contents, "DATA;", "ENDSEC;");
        auto data_formatted = fmt::fmt_data_section(data.slice);

        // Before & after section slices (header & footer)
        auto before_data = std::string_view{file_contents.data(), data.start_pos};
        auto after_data = std::string_view{file_contents.data() + data.end_pos, file_contents.size() - data.end_pos};

        // Write all sections to file
        output_file << before_data << std::endl;
        output_file << data_formatted;
        output_file << after_data << std::endl;

        // Close files
        input_file.close();
        output_file.close();
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