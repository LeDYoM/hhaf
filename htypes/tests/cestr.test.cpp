#include "catch.hpp"

#include <htypes/include/cestr.hpp>
#include <type_traits>

using namespace htps;

TEST_CASE("cestr::cestr", "[cestr]")
{
    {
        cestr a{""};
        CHECK(a.size() == 0U);
        CHECK(a.empty());
        CHECK(sizeof(a) == sizeof(char) * 1);
    }

    {
        cestr a{"Hello"};
        CHECK(a.size() == 5U);
        CHECK_FALSE(a.empty());
        CHECK(sizeof(a) == sizeof(char) * 6);
    }

    {
        cestr a{"a"};
        cestr b{"b"};
        cestr c{"hello"};
        CHECK(std::is_same_v<decltype(a), decltype(b)>);
        CHECK_FALSE(std::is_same_v<decltype(a), decltype(c)>);
        CHECK_FALSE(std::is_same_v<decltype(b), decltype(c)>);
    }
}
