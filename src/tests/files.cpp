#include <catch2/catch_test_macros.hpp>
#include <formatter/formatter.h>
#include <formatter/utils.h>
#include <string>
#include <array>

TEST_CASE("5. Golden file match check", "[formatting]")
{
    // Format all 3 files
    fmt::format_file("../../data/sample_01.ifc", "../../tests/output/sample_01_formatted.ifc");
    fmt::format_file("../../data/sample_02.ifc", "../../tests/output/sample_02_formatted.ifc");
    fmt::format_file("../../data/sample_03.ifc", "../../tests/output/sample_03_formatted.ifc");

    // Load 3 golden files
    std::array<std::string, 3> golden_files = {
        fmt::utils::str_read("../../tests/golden/sample_01.ifc"),
        fmt::utils::str_read("../../tests/golden/sample_02.ifc"),
        fmt::utils::str_read("../../tests/golden/sample_03.ifc")
    };

    // Load 3 formatted files
    std::array<std::string, 3> formatted_files = {
        fmt::utils::str_read("../../tests/output/sample_01_formatted.ifc"),
        fmt::utils::str_read("../../tests/output/sample_02_formatted.ifc"),
        fmt::utils::str_read("../../tests/output/sample_03_formatted.ifc")
    };

    // Check equality for all files
    for (int i = 0; i < 3; i++){
        REQUIRE(golden_files[i] == formatted_files[i]);
    }
}

TEST_CASE("6. Golden file idempotence check", "[formatting]")
{
    // Format golden files
    fmt::format_file("../../data/sample_01.ifc", "../../tests/output/sample_01_formatted_gf.ifc");
    fmt::format_file("../../data/sample_02.ifc", "../../tests/output/sample_02_formatted_gf.ifc");
    fmt::format_file("../../data/sample_03.ifc", "../../tests/output/sample_03_formatted_gf.ifc");

    // Load 3 golden files
    std::array<std::string, 3> golden_files = {
        fmt::utils::str_read("../../tests/golden/sample_01.ifc"),
        fmt::utils::str_read("../../tests/golden/sample_02.ifc"),
        fmt::utils::str_read("../../tests/golden/sample_03.ifc")
    };

    // Load 3 formatted files
    std::array<std::string, 3> formatted_files = {
        fmt::utils::str_read("../../tests/output/sample_01_formatted_gf.ifc"),
        fmt::utils::str_read("../../tests/output/sample_02_formatted_gf.ifc"),
        fmt::utils::str_read("../../tests/output/sample_03_formatted_gf.ifc")
    };

    // Check equality for all files
    for (int i = 0; i < 3; i++){
        REQUIRE(golden_files[i] == formatted_files[i]);
    }
}