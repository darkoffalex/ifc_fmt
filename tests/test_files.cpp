#include "pch.h"
#include <formatter/formatter.h>
#include <formatter/utils.h>

const std::string DATA_DIR = std::string(PROJECT_ROOT_DIR) + "/data/";
const std::string TESTS_OUT_DIR = std::string(PROJECT_ROOT_DIR) + "/tests/output/";
const std::string TESTS_GOLD_DIR = std::string(PROJECT_ROOT_DIR) + "/tests/golden/";

TEST_CASE("5. Golden file match check", "[formatting]")
{
    // Will run this test case 3 times with each value from list
    const std::string filename = GENERATE("sample_01", "sample_02", "sample_03");

    // Paths to files
    const std::string input_path = DATA_DIR + filename + ".ifc";
    const std::string output_path = TESTS_OUT_DIR + filename + "_formatted.ifc";
    const std::string golden_path = TESTS_GOLD_DIR + filename + ".ifc";

    // Format file
    fmt::format_file(input_path, output_path);

    // Read result and golden file
    std::string formatted_file = fmt::utils::str_read(output_path);
    std::string golden_file = fmt::utils::str_read(golden_path);

    // Check equality
    REQUIRE(formatted_file == golden_file);
}

TEST_CASE("6. Golden file idempotence check", "[formatting]")
{
    // Will run this test case 3 times with each value from list
    const std::string filename = GENERATE("sample_01", "sample_02", "sample_03");

    // Paths to files
    const std::string golden_path = TESTS_GOLD_DIR + filename + ".ifc";
    const std::string output_path = TESTS_OUT_DIR + filename + "_gf_formatted.ifc";

    // Format file
    fmt::format_file(golden_path, output_path);

    // Read result and golden file
    std::string formatted_file = fmt::utils::str_read(output_path);
    std::string golden_file = fmt::utils::str_read(golden_path);

    // Check equality
    REQUIRE(formatted_file == golden_file);
}