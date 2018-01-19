#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <parpar/include/parpar.hpp>

TEST_CASE("program", "[parpar]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program"}
    ));

    CHECK_FALSE(paramParser.hasParameters());
    CHECK(paramParser.hasValidSyntax());
    CHECK(paramParser.emptyParameters());
    CHECK(paramParser.numParameters() == 0);
    CHECK(paramParser.numSyntaxErrors() == 0);
    CHECK(paramParser.numPositionalParameters() == 0);
    CHECK(paramParser.numSwitchParameters() == 0);
    CHECK(paramParser.numOptionParameters() == 0);
}

TEST_CASE("program -", "[parpar][errors]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program ", "-"}
    ));

    CHECK_FALSE(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 1);
    CHECK(paramParser.numSyntaxErrors() == 1);
    CHECK(paramParser.numPositionalParameters() == 0);
    CHECK(paramParser.numSwitchParameters() == 0);
    CHECK(paramParser.numOptionParameters() == 1);
    CHECK(paramParser.errorAtParameter(0) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::OptionWithoutEqual);
}

TEST_CASE("program --abc file", "[parpar][positional][switch][errors]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program ", "--abc", "file"}
    ));

    CHECK_FALSE(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 2);
    CHECK(paramParser.numSyntaxErrors() == 1);
    CHECK(paramParser.numPositionalParameters() == 1);
    CHECK(paramParser.numSwitchParameters() == 1);
    CHECK(paramParser.numOptionParameters() == 0);
    CHECK(paramParser.errorAtParameter(0) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::NoError);
    CHECK(paramParser.errorAtParameter(1) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::IncorrectPositionalPosition);
}

TEST_CASE("program -abc=2 -abc=3", "[parpar][option][errors]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program ", "-abc=2", "-abc=3"}
    ));

    CHECK_FALSE(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 2);
    CHECK(paramParser.numSyntaxErrors() == 1);
    CHECK(paramParser.numPositionalParameters() == 0);
    CHECK(paramParser.numSwitchParameters() == 0);
    CHECK(paramParser.numOptionParameters() == 2);
    CHECK(paramParser.errorAtParameter(0) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::NoError);
    CHECK(paramParser.errorAtParameter(1) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::OptionAlreadySet);
}

TEST_CASE("program -abc -=3 -def=", "[parpar][syntax][option][errors]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program", "-abc", "-=3", "-def="}
    ));

    CHECK_FALSE(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 3);
    CHECK(paramParser.numSyntaxErrors() == 3);
    CHECK(paramParser.numPositionalParameters() == 0);
    CHECK(paramParser.numSwitchParameters() == 0);
    CHECK(paramParser.numOptionParameters() == 3);
    CHECK_FALSE(paramParser.hasValidSyntax());
    CHECK(paramParser.errorAtParameter(0) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::OptionWithoutEqual);

    CHECK(paramParser.errorAtParameter(1) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::EmptyOptionName);

    CHECK(paramParser.errorAtParameter(2) ==
        parpar::ParametersParser::
            SyntaxParserErrorCodes::EmptyOptionValue);
}

TEST_CASE("program filename --doit -abc=sdf", "[parpar][positional][option][switch]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program", "filename", "--doit", "-abc=sdf"}
    ));

    CHECK(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 3);
    CHECK(paramParser.numSyntaxErrors() == 0);
    CHECK(paramParser.numPositionalParameters() == 1);
    CHECK(paramParser.numSwitchParameters() == 1);
    CHECK(paramParser.numOptionParameters() == 1);
    CHECK(paramParser.positionalParameterAt(0) == "filename");
    CHECK(paramParser.positionalParameterAt(1) == "");
    CHECK(paramParser.switchExists("doit"));
    CHECK_FALSE(paramParser.switchExists("doitasd"));
}

TEST_CASE("program sourcef.dat targetf.dat --nope -abc=sdf -this=other", "[parpar][positional][option][switch]")
{
    const parpar::ParametersParser paramParser (parpar::create(
        {"program", "sourcef.dat", "targetf.dat", "--nope", "--ok", "-abc=sdf", "-this=other"}
    ));

    CHECK(paramParser.hasValidSyntax());
    CHECK_FALSE(paramParser.emptyParameters());
    CHECK(paramParser.hasParameters());
    CHECK(paramParser.numParameters() == 6);
    CHECK(paramParser.numSyntaxErrors() == 0);
    CHECK(paramParser.numPositionalParameters() == 2);
    CHECK(paramParser.numSwitchParameters() == 2);
    CHECK(paramParser.numOptionParameters() == 2);
    CHECK(paramParser.positionalParameterAt(0) == "sourcef.dat");
    CHECK(paramParser.positionalParameterAt(1) == "targetf.dat");
    CHECK(paramParser.switchExists("nope"));
    CHECK(paramParser.switchExists("ok"));
    CHECK_FALSE(paramParser.switchExists("doitasd"));
    CHECK(paramParser.optionExists("abc"));
    CHECK(paramParser.optionValue("abc").second == "sdf");
    CHECK(paramParser.optionValueOrDefault("abc","") == "sdf");
    CHECK(paramParser.optionExists("this"));
    CHECK(paramParser.optionValue("this").second == "other");
    CHECK(paramParser.optionValueOrDefault("this","") == "other");
    CHECK_FALSE(paramParser.optionExists("thisother"));
    CHECK_FALSE(paramParser.optionValue("thisother").first);
    CHECK(paramParser.optionValueOrDefault("thisother","") == "");
    CHECK(paramParser.optionValueOrDefault("another","42") == "42");
    CHECK(paramParser.optionValueOrDefault("another","false") == "false");
}
