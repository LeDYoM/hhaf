#include "catch_include.hpp"

#include <parpar/include/parpar_mini.h>
#include <htypes/include/str_functions.hpp>

using namespace htps;
using namespace parparmini;

TEST_CASE("haf::parpar::ParameterParserMini", "[parparmini]")
{
    const int argc           = 4;
    char const* const argv[] = {"parpar", "program=qwe.txt", "--abc", "-file"};

    const ParametersParserMini paramParser(create(argc, argv));

    CHECK(paramParser.numParameters() == 4U);

    CHECK(paramParser[0] == "parpar");
    CHECK(paramParser[1] == "program=qwe.txt");
    CHECK(paramParser[2] == "--abc");
    CHECK(paramParser[3] == "-file");

    CHECK(paramParser.param(0) == "parpar");
    CHECK(paramParser.param(1) == "program=qwe.txt");
    CHECK(paramParser.param(2) == "--abc");
    CHECK(paramParser.param(3) == "-file");
}

TEST_CASE("haf::parpar::ParameterParserMini_errors", "[parparmini]")
{
    const int argc           = 1;
    char const* const argv[] = {"parpar"};

    const ParametersParserMini paramParser(create(argc, argv));

    CHECK(paramParser.numParameters() == 1U);

    CHECK(paramParser[0] == "parpar");
    CHECK(paramParser[1] == nullptr);
    CHECK(paramParser[2] == nullptr);

    CHECK(paramParser.param(0) == "parpar");
    CHECK(paramParser.param(1) == nullptr);
    CHECK(paramParser.param(2) == nullptr);
}

TEST_CASE("haf::parpar::ParameterParserMini::str_view", "[parparmini]")
{
    const int argc           = 5;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt"};

    const ParametersParserMini paramParser(create(argc, argv));

    CHECK(paramParser["parpar"] == 0);
    CHECK(paramParser["--program"] == 1);
    CHECK(paramParser["this"] == 2);
    CHECK(paramParser["-file"] == 3);
    CHECK(paramParser["archive.txt"] == 4);

    CHECK(paramParser.param("parpar") == 0);
    CHECK(paramParser.param("--program") == 1);
    CHECK(paramParser.param("this") == 2);
    CHECK(paramParser.param("-file") == 3);
    CHECK(paramParser.param("archive.txt") == 4);
}

TEST_CASE("haf::parpar::ParameterParserMini::paramKkeyIndex", "[parparmini]")
{
    const int argc           = 6;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt", "---qwe"};

    const ParametersParserMini paramParser(create(argc, argv));
    CHECK(paramParser.paramKey(0) == "parpar");
    CHECK(paramParser.paramKey(1) == "program");
    CHECK(paramParser.paramKey(3) == "file");
    CHECK(paramParser.paramKey(4) == "archive.txt");
    CHECK(paramParser.paramKey(5) == "-qwe");
    CHECK(paramParser.paramKey(6) == nullptr);
}

TEST_CASE("haf::parpar::ParameterParserMini::paramKValueIndex", "[parparmini]")
{
    const int argc           = 6;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt", "---qwe"};

    const ParametersParserMini paramParser(create(argc, argv));
    CHECK(paramParser.paramValue(0) == "program");
    CHECK(paramParser.paramValue(1) == "this");
    CHECK(paramParser.paramValue(2) == "file");
    CHECK(paramParser.paramValue(3) == "archive.txt");
    CHECK(paramParser.paramValue(4) == "-qwe");
    CHECK(paramParser.paramValue(5) == nullptr);
}

TEST_CASE("haf::parpar::ParameterParserMini::paramKkeyStr", "[parparmini]")
{
    const int argc           = 5;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt"};

    const ParametersParserMini paramParser(create(argc, argv));
    CHECK(paramParser.paramKey("asfasdf") == 0);
    CHECK(paramParser.paramKey("parpar") == 0);
    CHECK(paramParser.paramKey("program") == 1);
    CHECK(paramParser.paramKey("this") == 2);
    CHECK(paramParser.paramKey("file") == 3);
    CHECK(paramParser.paramKey("archive.txt") == 4);
    CHECK(paramParser.paramKey("--program") == 0);
    CHECK(paramParser.paramKey("-file") == 0);
    CHECK(paramParser.paramKey("-program") == 0);
    CHECK(paramParser.paramKey("rogram") == 0);
    CHECK(paramParser.paramKey("archive") == 0);
}

TEST_CASE("haf::parpar::ParameterParserMini::paramValue", "[parparmini]")
{
    const int argc           = 5;
    char const* const argv[] = {"parpar", "--program", "this", "-file",
                                "archive.txt"};

    const ParametersParserMini paramParser(create(argc, argv));
    CHECK(paramParser.paramValue("asfasdf") == nullptr);
    CHECK(paramParser.paramValue("parpar") == nullptr);
    CHECK(paramParser.paramValue("program") == "this");
    CHECK(paramParser.paramValue("-program") == nullptr);
    CHECK(paramParser.paramValue("--program") == nullptr);
    CHECK(paramParser.paramValue("file") == "archive.txt");
    CHECK(paramParser.paramValue("-file") == nullptr);
    CHECK(paramParser.paramValue("archive.txt") == nullptr);
}
