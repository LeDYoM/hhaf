#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <parpar/include/parpar.hpp>

TEST_CASE("Command line without parameters works", "[parpar][syntax]")
{
    parpar::ParametersParser paramParser (parpar::create(
        {"program"}
    ));

    REQUIRE_FALSE(paramParser.hasParameters());
    REQUIRE(paramParser.numParameters() == 0);
    REQUIRE(paramParser.numSyntaxErrors() == 0);
    REQUIRE(paramParser.hasValidSyntax());
}

TEST_CASE("Command line with error syntax", "[parpar][syntax]")
{
    parpar::ParametersParser paramParser (parpar::create(
        {"program ", "-"}
    ));
}
