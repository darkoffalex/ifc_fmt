#include "pch.h"
#include <formatter/formatter.h>

namespace fmt
{
    std::string fmt_data_section(const std::string_view& section_slice)
    {
        // Formatted result (reserve to avoid re-allocations)
        std::string output;
        output.reserve(section_slice.size());

        // Statement string, flags & counters to track parsing state
        std::string current_statement{};
        current_statement.reserve(256);

        bool in_string = false;
        int paren_depth = 0;

        // Go through all symbols of data slice
        for (const char c : section_slice)
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

                    output += current_statement + '\n';
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

        return output;
    }
}
