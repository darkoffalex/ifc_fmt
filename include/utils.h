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
     * Slice info structure
     */
    struct SliceInfo
    {
        std::string_view slice;
        size_t start_token_len;
        size_t end_token_len;
        size_t start_pos;
        size_t end_pos;
    };

    /**
     * Get a slice of string
     * @param str Source string
     * @param start Start token
     * @param end End token
     * @return Slice info structure
     */
    inline SliceInfo str_slice(const std::string& str, const std::string& start, const std::string& end)
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
        SliceInfo si{};
        si.start_pos = start_pos + start.size();
        si.end_pos = end_pos;
        si.start_token_len = start.size();
        si.end_token_len = end.size();
        si.slice = std::string_view{str.data() + si.start_pos, si.end_pos - si.start_pos};
        return si;
    }
}