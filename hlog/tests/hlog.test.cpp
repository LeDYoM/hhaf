#pragma warning(push)
#pragma warning(disable : 4514 4620 4623 4625 4626 4820 5026 5027 5204)
#include "catch.hpp"
#pragma warning(pop)

#include <hlog/include/hlog.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("hlog", "[hlog]")
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