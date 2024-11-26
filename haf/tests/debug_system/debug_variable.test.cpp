#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/debug_system/debug_variable.hpp>

using namespace htps;
using namespace haf::debug;

TEST_CASE("DebugVariable::DebugVariable")
{
    DebugVariable debug_variable{0U};
    CHECK(debug_variable.value() == 0);
    CHECK(debug_variable.frame() == 0);
}

TEST_CASE("DebugVariable::incrementFrame()")
{
    DebugVariable debug_variable{0U};
    CHECK(debug_variable.value() == 0);
    debug_variable.incrementFrame();
    CHECK(debug_variable.frame() == 1);
}

TEST_CASE("DebugVariable::operator+=()")
{
    DebugVariable debug_variable{0U};
    CHECK(debug_variable.value() == 0);
    debug_variable += 4;
    CHECK(debug_variable.value() == 4);
}

TEST_CASE("DebugVariable::operator+()")
{
    DebugVariable debug_variable{0U};
    DebugVariable debug_variable2{5U};
    CHECK(debug_variable.value() == 0);
    CHECK(debug_variable2.value() == 5);
    debug_variable = debug_variable2 + 3;
    CHECK(debug_variable.value() == 8);
}

TEST_CASE("DebugVariable::valuePerFrame")
{
    DebugVariable debug_variable{0U};
    debug_variable += 10;
    CHECK(debug_variable.valuePerFrame() == static_cast<f64>(10));
    debug_variable.incrementFrame();
    debug_variable += 6;
    CHECK(debug_variable.valuePerFrame() == static_cast<f64>(16));
    debug_variable.incrementFrame();
    CHECK(debug_variable.valuePerFrame() == static_cast<f64>(8));
}

TEST_CASE("DebugVariable::copy constructor")
{
    DebugVariable debug_variable{5U};
    debug_variable.incrementFrame();
    CHECK(debug_variable.value() == 5U);
    CHECK(debug_variable.frame() == 1U);

    DebugVariable debug_variable2{debug_variable};
    CHECK(debug_variable2.value() == 5U);
    CHECK(debug_variable2.frame() == 1U);
}

TEST_CASE("DebugVariable::copy assignment")
{
    DebugVariable debug_variable{5U};
    debug_variable.incrementFrame();
    CHECK(debug_variable.value() == 5U);
    CHECK(debug_variable.frame() == 1U);

    DebugVariable debug_variable2{1U};
    debug_variable2.incrementFrame();
    debug_variable2.incrementFrame();

    CHECK(debug_variable2.value() == 1U);
    CHECK(debug_variable2.frame() == 2U);

    debug_variable2 = debug_variable;
    CHECK(debug_variable2.value() == 5U);
    CHECK(debug_variable2.frame() == 1U);
}

TEST_CASE("DebugVariable::assign debug variables maintains frame")
{
    DebugVariable debug_variable{5U};
    debug_variable.incrementFrame();
    CHECK(debug_variable.value() == 5U);
    CHECK(debug_variable.frame() == 1U);

    DebugVariable debug_variable2{1U};
    debug_variable2.incrementFrame();
    debug_variable2.incrementFrame();

    debug_variable = debug_variable2.value();
    CHECK(debug_variable.value() == 1U);
    CHECK(debug_variable.frame() == 1U);
}

TEST_CASE("DebugVariable::increment debug variables maintains frame")
{
    DebugVariable debug_variable{5U};
    debug_variable.incrementFrame();
    CHECK(debug_variable.value() == 5U);
    CHECK(debug_variable.frame() == 1U);

    DebugVariable debug_variable2{1U};
    debug_variable2.incrementFrame();
    debug_variable2.incrementFrame();

    debug_variable += debug_variable2.value();
    CHECK(debug_variable.value() == 6U);
    CHECK(debug_variable.frame() == 1U);
}
