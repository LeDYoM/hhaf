#pragma warning(push)
#pragma warning(disable : 4514 4620 4623 4625 4626 4820 5026 5027 5204)
#include "catch.hpp"
#pragma warning(pop)

#include <hlog/include/hlog.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("hlogdisplayer", "[hlog][hlogdisplayer")
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

TEST_CASE("hlogdisplayerWithMessage", "[hlog][hlogdisplayer")
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

TEST_CASE("hlogdisplayerWithMessageWithSeveirty", "[hlog][hlogdisplayer")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::debug>, true>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should be used");
    CHECK(testing_stream() == "<DEBUG> :This should be used");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE> :This too");

    LogTestNullCommit::finish_log();
}
