#include "catch_include.hpp"

#include <logger/include/log.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("log", "[logger]")
{
    {
        using TestingLog =
            logger::Log<true, LogStreamTest, logger::NullCommiter>;

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