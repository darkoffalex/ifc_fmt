#include <catch2/catch_test_macros.hpp>
#include <formatter/formatter.h>

TEST_CASE("1. Whitespace removal outside strings", "[formatting]")
{
    const std::string input = "  #1 = IFCPERSON ( $ , $ ) ;  ";
    const std::string expected = "#1=IFCPERSON($,$);\n";
    REQUIRE(fmt::fmt_data_section(input) == expected);
}

TEST_CASE("2. Strings preserved exactly (including '')", "[formatting]")
{
    const std::string input = "#2=IFCORGANIZATION($, 'Org  Name with ''quotes'' ', $, $);";
    const std::string expected = "#2=IFCORGANIZATION($,'Org  Name with ''quotes'' ',$,$);\n";
    REQUIRE(fmt::fmt_data_section(input) == expected);
}

TEST_CASE("3. Nested parentheses handled correctly", "[formatting]")
{
    const std::string input = "#9 = IFCUNITASSIGNMENT ( ( #6 , #7 , #8 ) ) ;";
    const std::string expected = "#9=IFCUNITASSIGNMENT((#6,#7,#8));\n";
    REQUIRE(fmt::fmt_data_section(input) == expected);
    REQUIRE_THROWS_AS(fmt::fmt_data_section("#1=A( ;"), std::runtime_error);
}

TEST_CASE("4. Multiple statements on one line become one-per-line", "[formatting]")
{
    const std::string input = "#1=IFCPERSON($,$,$,$,$,$,$,$); #2=IFCORGANIZATION($,'Org',$,$,$);";
    const std::string expected =
        "#1=IFCPERSON($,$,$,$,$,$,$,$);\n"
        "#2=IFCORGANIZATION($,'Org',$,$,$);\n";

    REQUIRE(fmt::fmt_data_section(input) == expected);
}