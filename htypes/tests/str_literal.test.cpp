#include "catch.hpp"

#include <htypes/include/str_literal.hpp>
#include <type_traits>

using namespace htps;

TEST_CASE("str_literal::str_literal", "[str_literal]")
{
    {
        str_literal a{""};
        CHECK(a.size() == 0U);
        CHECK(a.empty());
        CHECK(sizeof(a) == (sizeof(char) * 1));
    }

    {
        str_literal a{"Hello"};
        CHECK(a.size() == 5U);
        CHECK_FALSE(a.empty());
        CHECK(sizeof(a) == sizeof(char) * 6);
    }

    {
        str_literal a{"a"};
        str_literal b{"b"};
        str_literal c{"hello"};
        CHECK_FALSE(a.empty());
        CHECK_FALSE(b.empty());
        CHECK_FALSE(c.empty());
        CHECK(std::is_same_v<decltype(a), decltype(b)>);
        CHECK_FALSE(std::is_same_v<decltype(a), decltype(c)>);
        CHECK_FALSE(std::is_same_v<decltype(b), decltype(c)>);

        str_literal d{"hello"};
        CHECK(c == d);
        CHECK(c == "hello");
        CHECK_FALSE(c == "");
        CHECK_FALSE(c == "hello2");
    }
}
