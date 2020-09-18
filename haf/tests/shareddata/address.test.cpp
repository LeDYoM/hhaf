#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <haf/shareddata/include/address.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::shdata;

TEST_CASE("Address construction", "[haf][shdata][Address]")
{
    SECTION("Normal")
    {
        Address address("abc/def");
        CHECK(address.size() == 2U);
        CHECK_FALSE(address.empty());
        CHECK(address[0U] == "abc");
        CHECK(address[1U] == "def");
        CHECK(address.first() == "abc");
        CHECK(address.last() == "def");
    }

    SECTION("Separator at the beggining")
    {
        Address address("/resource/temp");
        CHECK(address.size() == 3U);
        CHECK_FALSE(address.empty());
        CHECK(address[0U] == "");
        CHECK(address[1U] == "resource");
        CHECK(address[2U] == "temp");
        CHECK(address.first() == "");
        CHECK(address.last() == "temp");
    }

    SECTION("Separator at the end")
    {
        Address address("qwe/asd/");
        CHECK(address.size() == 3U);
        CHECK_FALSE(address.empty());
        CHECK(address[0U] == "qwe");
        CHECK(address[1U] == "asd");
        CHECK(address[2U] == "");
        CHECK(address.first() == "qwe");
        CHECK(address.last() == "");
    }

    SECTION("Separator at the beggining and the end")
    {
        Address address("/qwe/asd/");
        CHECK(address.size() == 4U);
        CHECK_FALSE(address.empty());
        CHECK(address[0U] == "");
        CHECK(address[1U] == "qwe");
        CHECK(address[2U] == "asd");
        CHECK(address[3U] == "");
        CHECK(address.first() == "");
        CHECK(address.last() == "");
    }

    SECTION("Separator at the beggining and the end and the middle")
    {
        Address address("/qwe//asd/");
        CHECK(address.size() == 5U);
        CHECK_FALSE(address.empty());
        CHECK(address[0U] == "");
        CHECK(address[1U] == "qwe");
        CHECK(address[2U] == "");
        CHECK(address[3U] == "asd");
        CHECK(address[4U] == "");
        CHECK(address.first() == "");
        CHECK(address.last() == "");
    }
}
