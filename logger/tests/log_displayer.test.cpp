#include "catch_include.hpp"
#include <logger/include/log_displayer.hpp>
#include <logger/include/severity_type.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("logdisplayer", "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::verbose>>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should not be used");
    CHECK(testing_stream() == "");

    TestLogDisplayer::verbose("This should be used");
    CHECK(testing_stream() == "This should be used");

    LogTestNullCommit::finish_log();
}

TEST_CASE("logdisplayerWithoutMessage", "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::debug>>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "This should be used");

    LogTestNullCommit::finish_log();
}

TEST_CASE("logdisplayerWithMessage", "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::debug>,false,"MySuperSystem: ">;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "MySuperSystem: This should be used");

    LogTestNullCommit::finish_log();
}

TEST_CASE("logdisplayerWithoutMessageWithSeveirty", "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::debug>, true>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "<DEBUG>: This should be used");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE>: This too");

    LogTestNullCommit::finish_log();
}

TEST_CASE("logdisplayerWithMessageWithSeveirty", "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::debug>, true, "MyOtherSuperSystem: ">;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "<DEBUG>: MyOtherSuperSystem: This should be used");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE>: MyOtherSuperSystem: This too");

    LogTestNullCommit::finish_log();
}
