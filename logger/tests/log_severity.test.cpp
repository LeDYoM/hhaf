#include "catch_include.hpp"
#include <logger/include/log_displayer.hpp>
#include <logger/include/severity_type.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("logdisplayerWithoutMessageWithSomeSeveirty",
          "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::verbose>,
        true>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should not be used");
    CHECK(testing_stream() == "");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE>: This too");

    LogTestNullCommit::finish_log();
}

TEST_CASE("logdisplayerWithMessageWithSomeSeveirty",
          "[logger][log_severity][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::verbose>,
        true, "MyOtherSuperSystem: ">;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE>: MyOtherSuperSystem: This too");

    LogTestNullCommit::finish_log();
}
