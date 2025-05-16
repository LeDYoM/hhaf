#include "catch_include.hpp"

#include <parpar/include/parpar_mini.h>
#include <htypes/include/str_functions.hpp>

using namespace htps;
using namespace parparmini;
/*
TEST_CASE("haf::parpar::ParameterParserMini", "[parparmini]")
{
    {
        const int argc           = 4;
        char const* const argv[] = {"parpar", "program=qwe.txt", "--abc",
                                    "-file"};

        const ParametersParserMini paramParser(create(argc, argv));

        CHECK(paramParser.numParameters() == 4U);

        CHECK(strncmp(paramParser[0], "parpar") == 0);
        CHECK(strncmp(paramParser[1], "program=qwe.txt") == 0);
        CHECK(strncmp(paramParser[2], "--abc") == 0);
        CHECK(strncmp(paramParser[3], "-file") == 0);

        CHECK(strncmp(paramParser.param(0), "parpar") == 0);
        CHECK(strncmp(paramParser.param(1), "program=qwe.txt") == 0);
        CHECK(strncmp(paramParser.param(2), "--abc") == 0);
        CHECK(strncmp(paramParser.param(3), "-file") == 0);
    }

    {
        const int argc           = 1;
        char const* const argv[] = {"parpar"};

        const ParametersParserMini paramParser(create(argc, argv));

        CHECK(paramParser.numParameters() == 1U);

        CHECK(strncmp(paramParser[0], "parpar") == 0);
        CHECK(strncmp(paramParser[1], "program=qwe.txt") != 0);
        CHECK(paramParser[1] == nullptr);

        CHECK(strncmp(paramParser.param(0), "parpar") == 0);
        CHECK(strncmp(paramParser.param(1), "program=qwe.txt") != 0);
        CHECK(paramParser.param(1) == nullptr);
    }
}

TEST_CASE("haf::parpar::ParameterParserMini", "[parparmini]")
{
    const int argc           = 5;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt"};

    const ParametersParserMini paramParser(create(argc, argv));


}
*/
