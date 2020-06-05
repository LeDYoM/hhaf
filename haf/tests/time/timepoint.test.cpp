#include "catch.hpp"

#include <haf/time/include/timepoint.hpp>

using namespace haf::time;

TEST_CASE("TimePoint default constructor")
{
    TimePoint const time_point;
    using Rep = TimePoint::Rep;

    CHECK(time_point.nanoseconds() == Rep{0U});
    CHECK(time_point.microseconds() == Rep{0U});
    CHECK(time_point.milliseconds() == Rep{0U});
    CHECK(time_point.seconds() == Rep{0U});
}

TEST_CASE("TimePoint operators")
{
    TimePoint time_point;
    using Rep = TimePoint::Rep;

    CHECK(time_point.nanoseconds() == Rep{0U});
    CHECK(time_point.microseconds() == Rep{0U});
    CHECK(time_point.milliseconds() == Rep{0U});
    CHECK(time_point.seconds() == Rep{0U});

    time_point += TimePoint(5000000000U);

    CHECK(time_point.nanoseconds() == Rep{5000000000U});
    CHECK(time_point.microseconds() == Rep{5000000U});
    CHECK(time_point.milliseconds() == Rep{5000U});
    CHECK(time_point.seconds() == Rep{5U});

    time_point -= TimePoint(2000000000U);

    CHECK(time_point.nanoseconds() == Rep{3000000000U});
    CHECK(time_point.microseconds() == Rep{3000000U});
    CHECK(time_point.milliseconds() == Rep{3000U});
    CHECK(time_point.seconds() == Rep{3U});
}