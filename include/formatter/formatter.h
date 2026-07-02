#pragma once

#include <string>
#include <string_view>

namespace fmt
{
    /**
     * Formats DATA section
     * @param section_slice Data section slice
     * @return Formatted section string
     */
    std::string format_data_section(const std::string_view& section_slice);

    /**
     * Format ICF file
     * @param input_file Input file path
     * @param output_file Output file path
     */
    void format_file(const std::string& input_file, const std::string& output_file);
}