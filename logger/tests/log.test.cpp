#include "catch_include.hpp"
#include "include/log_stream_test.hpp"

import logger;
import htypes;

using namespace logger;

class LogStreamTest
{
    inline static htps::str data = htps::str{""};

public:
    htps::str& operator()() { return data; }
};

using LogTestNullCommit =
    logger::Log<true, LogStreamTest, logger::NullCommiter>;

using LogTestThreadNullCommit = logger::
    Log<true, LogStreamTest, logger::ThreadCommiter<logger::NullCommiter>>;

TEST_CASE("log", "[logger]")
{
    {
        using TestingLog = Log<true, LogStreamTest, logger::NullCommiter>;

        TestingLog::init_log();
        LogStreamTest testing_stream;

        TestingLog::log("Hello world");
        CHECK(testing_stream() == "Hello world");

        TestingLog::log("Hello world2");
        CHECK(testing_stream() == "Hello world2");

        TestingLog::finish_log();
    }
    {
        using TestingLog =
            logger::Log<false, LogStreamTest, logger::NullCommiter>;

        TestingLog::init_log();
        LogStreamTest testing_stream;

        TestingLog::log("Hello world");
        CHECK(testing_stream() == "");

        TestingLog::log("Hello world2");
        CHECK(testing_stream() == "");

        TestingLog::finish_log();
    }
}
