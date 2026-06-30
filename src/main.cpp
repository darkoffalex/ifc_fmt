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
        // Data section slice
        auto data = utils::str_slice(file_contents, "DATA;", "ENDSEC;");
        // Before & after section slices
        auto before_data = std::string_view{file_contents.data(), data.start_pos};
        auto after_data = std::string_view{file_contents.data() + data.end_pos, file_contents.size() - data.end_pos};

        // Write header
        output_file << before_data << std::endl;

        // Statement string, flags & counters to track parsing state
        std::string current_statement{};
        bool in_string = false;
        int paren_depth = 0;

        // Go through all symbols of data slice
        for (char c : data.slice)
        {
            // String literals stats/ends
            if (c == '\'')
            {
                in_string = !in_string;
                current_statement += c;
                continue;
            }

            // Currently handling string literal - just add symbol
            if (in_string)
            {
                current_statement += c;
            }
            // Not string literal
            else
            {
                // Ignore all spaces & end-lines
                if (std::isspace(static_cast<unsigned char>(c))) {
                    continue;
                }
                // Handle opening parenthesis
                if (c == '(')
                {
                    paren_depth++;
                }
                // Handle closing parenthesis
                else if (c == ')')
                {
                    paren_depth--;
                    if (paren_depth < 0){
                        throw std::runtime_error("Unmatched parenthesis");
                    }
                }

                current_statement += c;

                // Handle statement end
                if (c == ';'){
                    if (paren_depth != 0){
                        throw std::runtime_error("Unmatched parenthesis");
                    }

                    output_file << current_statement << std::endl;
                    current_statement.clear();
                }
            }
        }

        // Handle unterminated statement cases
        if (!current_statement.empty()){
            throw std::runtime_error("Unterminated statement before EOF");
        }
        if (in_string){
            throw std::runtime_error("Unterminated string literal before end of DATA section");
        }

        // Write footer
        output_file << after_data << std::endl;

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
