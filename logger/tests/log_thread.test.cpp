#include "catch_include.hpp"
#include <logger/include/log_displayer.hpp>
#include <logger/include/severity_type.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("log_thread_commiter", "[logger][threadcommiter][logdisplayer]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestThreadNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::verbose>,
        true>;

    LogTestThreadNullCommit::init_log();
    LogStreamTest testing_stream;

    TestLogDisplayer::debug("This should not be used");
    CHECK(testing_stream() == "");
    TestLogDisplayer::verbose("This too");
    CHECK(testing_stream() == "<VERBOSE>: This too");
    TestLogDisplayer::verbose("This 3");
    CHECK(testing_stream() == "<VERBOSE>: This 3");
    TestLogDisplayer::verbose("This 4");
    CHECK(testing_stream() == "<VERBOSE>: This 4");

    LogTestThreadNullCommit::finish_log();
}
