#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/menum.hpp>
#include <limits>

using namespace lib;

enum class A : s32
{
    min = 0,
    max = 2,
    TestValue1 = min,
    TestValue2 = min + 1,
    TestValue3 = max
};

str to_str(const A value)
{
    switch (value)
    {
    case A::TestValue1:
        return "TestValue1";
        break;
    case A::TestValue2:
        return "TestValue2";
        break;
    case A::TestValue3:
        return "TestValue3";
        break;
    }
    return "";
}

TEST_CASE("menum", "[menum]")
{
    static_assert(MEnum<A>::min == A::min, "Error in min");
    static_assert(MEnum<A>::max == A::max, "Error in max");

    A a{A::TestValue1};
    CHECK(a == A::min);
    CHECK(a == A::TestValue1);

    A a1{A::TestValue3};
    CHECK(a1 == A::max);
    CHECK(a1 == A::TestValue3);
}
