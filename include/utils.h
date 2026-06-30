#pragma once

namespace utils
{
    /**
     * Read file to string
     * @param stream Input file stream
     * @return File content string
     */
    inline std::string read_to_string(std::ifstream& stream)
    {
        // Get size in bytes
        stream.seekg(0, std::ios::end);
        const auto file_size = stream.tellg();
        stream.seekg(0, std::ios::beg);

        // Read & return content as string
        if (file_size > 0){
            std::string content;
            content.reserve(file_size);
            content.assign(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
            return content;
        }

        return "";
    }

    /**
     * Get a slice of string
     * @param str Source string
     * @param start Start keyword
     * @param end End keyword
     * @return Slice string view
     * @throws std::runtime_error
     */
    inline std::string_view str_slice(const std::string& str, const std::string& start, const std::string& end)
    {
        // Find start position
        const size_t start_pos = str.find(start);
        if (start_pos == std::string::npos){
            throw std::runtime_error("Can't find start of section (" + start + ")");
        }

        // Find end position
        const size_t end_pos = str.find(end, start_pos + start.size());
        if (end_pos == std::string::npos){
            throw std::runtime_error("Can't find end of section (" + end + ")");
        }

        // Get slice
        const size_t content_start = start_pos + start.size();
        const size_t content_length = end_pos - content_start;
        return std::string_view{str.data() + content_start, content_length};
    }
}