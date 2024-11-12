#include "catch.hpp"

#include <htypes/include/str_view.hpp>

using namespace htps;

TEST_CASE("str_view::str_view Default constructor", "[str_view]")
{
    str_view a{"asd"};
    CHECK(a.size_ == a.size());
    CHECK(a.size() == 3U);

    CHECK(a[0U] == 'a');
    CHECK(a[1U] == 's');
    CHECK(a[2U] == 'd');
    CHECK(a[3U] == static_cast<char>(0));
}

TEST_CASE("str_view::str_view Constructor with nullptr", "[str_view]")
{
    str_view a{nullptr};
    CHECK(a.size_ == a.size());
    CHECK(a.size() == 0U);
    CHECK(a.empty());
}

TEST_CASE("str_view::str_view Constructor with empty string", "[str_view]")
{
    str_view a{""};
    CHECK(a.size_ == a.size());
    CHECK(a.size() == 0U);
    CHECK(a.empty());
}

TEST_CASE("str_view::operator==", "[str_view]")
{
    str_view a{"hello"};
    CHECK(a.size_ == 5U);
    CHECK_FALSE(a.empty());
    CHECK(a == "hello");

    SECTION("Almost equal")
    {
        str_view a1{"TestComponent2"};
        str_view a2{"TestComponent3"};
        CHECK(a1 != a2);
        CHECK(a1 != "TestComponent3");
        CHECK(a1 == "TestComponent2");
    }
}
