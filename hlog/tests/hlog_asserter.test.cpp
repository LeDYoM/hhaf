#pragma warning(push)
#pragma warning(disable : 4514 4620 4623 4625 4626 4820 5026 5027 5204)
#include "catch.hpp"
#pragma warning(pop)

#include <hlog/include/hlog.hpp>
#include "include/log_stream_test.hpp"

TEST_CASE("logasserter_0", "[hlog][hlogasseter]")
{
    using TestLogDisplayer = logger::LogDisplayer<
        LogTestNullCommit,
        logger::SeverityTypeActiveTo<
            logger::SeverityTypeDefinition::severity_type_t::verbose>>;

    LogTestNullCommit::init_log();
    LogStreamTest testing_stream;

    using Asserter = logger::LogAsserter<TestLogDisplayer>;

    Asserter::log_assert(true, "This should not be used");
    CHECK(testing_stream() == "");

    Asserter::UseLowLevelAssert = false;
    Asserter::log_assert(false, "This should not crash");
    CHECK(testing_stream() != "");

}
