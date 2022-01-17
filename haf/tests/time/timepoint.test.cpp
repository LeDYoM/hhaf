#include "catch.hpp"

#include <haf/include/time/time_point.hpp>
#include <htypes/include/str.hpp>

#include <type_traits>

using namespace haf::time;

static_assert(std::is_default_constructible_v<TimePoint>);
static_assert(std::is_trivially_move_constructible_v<TimePoint>);
static_assert(std::is_trivially_move_assignable_v<TimePoint>);
static_assert(std::is_trivially_copyable_v<TimePoint>);
static_assert(std::is_trivially_copy_assignable_v<TimePoint>);

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

    SECTION("Internal operators")
    {
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

        time_point *= 2;

        CHECK(time_point.nanoseconds() == Rep{6000000000U});
        CHECK(time_point.microseconds() == Rep{6000000U});
        CHECK(time_point.milliseconds() == Rep{6000U});
        CHECK(time_point.seconds() == Rep{6U});

        time_point /= 3;

        CHECK(time_point.nanoseconds() == Rep{2000000000U});
        CHECK(time_point.microseconds() == Rep{2000000U});
        CHECK(time_point.milliseconds() == Rep{2000U});
        CHECK(time_point.seconds() == Rep{2U});
    }

    SECTION("Free functions operators")
    {
        time_point = TimePoint{10U};
        CHECK(time_point.nanoseconds() == Rep{10U});

        {
            TimePoint time_point2 = time_point + TimePoint{15U};
            CHECK(time_point2.nanoseconds() == Rep{25U});
        }

        {
            TimePoint time_point2 = time_point - TimePoint{1U};
            CHECK(time_point2.nanoseconds() == Rep{9U});
        }

        {
            TimePoint time_point2 = time_point * 2U;
            CHECK(time_point2.nanoseconds() == Rep{20U});
        }

        {
            TimePoint time_point2 = time_point / 2U;
            CHECK(time_point2.nanoseconds() == Rep{5U});
        }
    }
}

TEST_CASE("TimePoint function constructors")
{
    TimePoint time_point{5000000000U};

    {
        TimePoint time_point2 = TimePoint_as_nanoseconds(5000000000U);
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 = TimePoint_as_microseconds(5000000U);
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 = TimePoint_as_miliseconds(5000U);
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 = TimePoint_as_seconds(5U);
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 = TimePoint_as_seconds_f32(5.F);
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 =
            TimePoint_as_nanoseconds(time_point.nanoseconds());
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 =
            TimePoint_as_microseconds(time_point.microseconds());
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 =
            TimePoint_as_miliseconds(time_point.milliseconds());
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 = TimePoint_as_seconds(time_point.seconds());
        CHECK(time_point == time_point2);
    }

    {
        TimePoint time_point2 =
            TimePoint_as_seconds_f32(time_point.seconds_f32());
        CHECK(time_point == time_point2);
    }
}

TEST_CASE("TimePoint comparison operators")
{
    TimePoint time_point{5000000000U};
    TimePoint time_point2{5000000000U};
    TimePoint time_lower{4999999999U};
    TimePoint time_higher{5000000001U};

    CHECK(time_point == time_point2);
    CHECK_FALSE(time_point != time_point2);
    CHECK(time_point <= time_point2);
    CHECK(time_point >= time_point2);

    CHECK(time_point > time_lower);
    CHECK(time_point >= time_lower);
    CHECK_FALSE(time_point > time_higher);
    CHECK_FALSE(time_point >= time_higher);
    CHECK_FALSE(time_point == time_lower);
    CHECK(time_point != time_lower);

    CHECK(time_point < time_higher);
    CHECK(time_point <= time_higher);
    CHECK_FALSE(time_point > time_higher);
    CHECK_FALSE(time_point >= time_higher);
    CHECK_FALSE(time_point == time_higher);
    CHECK(time_point != time_higher);
}

TEST_CASE("TimePoint output operator")
{
    TimePoint time_point{500U};
    htps::str result("The result: ");
    result << time_point;
    CHECK(result == "The result: 500");
}
