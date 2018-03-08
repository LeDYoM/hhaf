#include "catch.hpp"

#include <mtypes/include/timer.hpp>

using namespace lib;

TEST_CASE("timer basic check", "[timer]")
{
    Timer t;
    // Could fail by debugging.
    CHECK(t.getElapsedTime().asSeconds() < 1.0);
}
