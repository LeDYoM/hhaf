#include "catch_include.hpp"

#include <htypes/include/str_view.hpp>

using namespace htps;

TEST_CASE("str_view::str_view Default constructor", "[str_view]")
{
    str_view a{"asd"};
    CHECK(a.m_size == a.size());
    CHECK(a.size() == 3U);

    CHECK(a[0U] == 'a');
    CHECK(a[1U] == 's');
    CHECK(a[2U] == 'd');
    CHECK(a[3U] == static_cast<char>(0));
}

TEST_CASE("str_view::str_view Constructor with nullptr", "[str_view]")
{
    str_view a{nullptr};
    CHECK(a.m_size == a.size());
    CHECK(a.size() == 0U);
    CHECK(a.empty());
}

TEST_CASE("str_view::str_view Constructor with empty string", "[str_view]")
{
    str_view a{""};
    CHECK(a.m_size == a.size());
    CHECK(a.size() == 0U);
    CHECK(a.empty());
}

TEST_CASE("str_view::operator==", "[str_view]")
{
    str_view a{"hello"};
    CHECK(a.m_size == 5U);
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

TEST_CASE("str_view::operator<=>", "[str_view]")
{
    {
        str_view a{"hello"};
        CHECK(a.m_size == 5U);
        CHECK_FALSE(a.empty());
        CHECK(a > "helli");
        CHECK_FALSE(a < "helli");
        CHECK_FALSE(a == "helli");
        CHECK("helli" != a);
        CHECK("helli" < a);
        CHECK_FALSE("helli" > a);
        CHECK_FALSE("helli" == a);
        CHECK("helli" != a);
    }

    {
        str_view a{"hello"};
        CHECK(a < "hellooooooo");

        CHECK(str_view{"hello"} < "hellooooooo");
    }
}

TEST_CASE("str_view::find", "[str_view]")
{
    {
        str_view a{"Hello"};
        CHECK(a.find("hello") == npos);
    }

    {
        str_view a{"Hello"};
        CHECK(a.find("Hello") == 0U);
    }

    {
        str_view a{"Hello"};
        CHECK(a.find("u") == npos);
    }

    {
        str_view a{"Hello"};
        CHECK(a.find("o") == 4U);
    }

    {
        str_view a{"Hello"};
        CHECK(a.find("H") == 0U);
    }

    {
        str_view a{"Hello"};
        CHECK(a.find("Hello ") == npos);
    }
}
