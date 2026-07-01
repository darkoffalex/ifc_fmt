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
    std::string fmt_data_section(const std::string_view& section_slice);
}