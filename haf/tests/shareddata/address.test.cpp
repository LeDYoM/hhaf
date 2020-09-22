#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/object.hpp>
#include <haf/shareddata/include/address.hpp>

using namespace mtps;
using namespace haf;
using namespace haf::shdata;

TEST_CASE("Address", "[haf][shdata][Address]")
{
    SECTION("Normal")
    {
        Address address("abc/def");
        CHECK(address.size() == 2U);
        CHECK(address[0U] == "abc");
        CHECK(address[1U] == "def");
        CHECK(address.first() == "abc");
        CHECK(address.last() == "def");
    }

    SECTION("Separator at the beggining")
    {
        Address address("/resource/temp");
        CHECK(address.size() == 3U);
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
        CHECK(address[0U] == "");
        CHECK(address[1U] == "qwe");
        CHECK(address[2U] == "");
        CHECK(address[3U] == "asd");
        CHECK(address[4U] == "");
        CHECK(address.first() == "");
        CHECK(address.last() == "");
    }

    SECTION("Relative, final and opposites")
    {
        {
            Address address("");
            CHECK(address.size() == 1U);
            CHECK(address.isAbsolute());
            CHECK_FALSE(address.isRelative());
            CHECK(address.isFinal());
            CHECK_FALSE(address.isNotFinal());
        }
        {
            Address address("/");
            CHECK(address.size() == 2U);
            CHECK(address.isAbsolute());
            CHECK_FALSE(address.isRelative());
            CHECK(address.isFinal());
            CHECK_FALSE(address.isNotFinal());
        }

        {
            Address address("abc");
            CHECK(address.size() == 1U);
            CHECK_FALSE(address.isAbsolute());
            CHECK(address.isRelative());
            CHECK_FALSE(address.isFinal());
            CHECK(address.isNotFinal());
        }

        {
            Address address("/abc/def/");
            CHECK(address.size() == 4U);
            CHECK(address.isAbsolute());
            CHECK_FALSE(address.isRelative());
            CHECK(address.isFinal());
            CHECK_FALSE(address.isNotFinal());
        }

        {
            Address address("/abc/def");
            CHECK(address.size() == 3U);
            CHECK(address.isAbsolute());
            CHECK_FALSE(address.isRelative());
            CHECK_FALSE(address.isFinal());
            CHECK(address.isNotFinal());
        }

        {
            Address address("abc/def/");
            CHECK(address.size() == 3U);
            CHECK_FALSE(address.isAbsolute());
            CHECK(address.isRelative());
            CHECK(address.isFinal());
            CHECK_FALSE(address.isNotFinal());
        }
    }
}

TEST_CASE("applyAddress", "[haf][shdata][Address][Object]")
{
    Object obj
    {
        { "key1",
            {
                { "subkey1", "subvalue1" }
            }
        },
        { "abc",
            {
                { "subkey2", "subvalue2" }
            }
        },
        { "abc",
            Object{ {"def",
                Object {
                    { "subsubkey1", "subsubvalue" }
                }
            } }
        }
    };
    
    {
        Address address("abc/def/");
        auto const result = objectFromAddress(address, obj);
        CHECK(result.first);
        CHECK(result.second["subsubkey1"].getValue() == "subsubvalue");
        CHECK(result.second == obj["abc"]["def"].getObject());
    }

    {
        auto const result = objectFromAddress(Address{"abc/def"}, obj);
        CHECK_FALSE(result.first);
    }

    {
        auto const result = objectFromAddress(Address{"abc/def1/"}, obj);
        CHECK_FALSE(result.first);
    }

    {
        auto const result = objectFromAddress(Address{"/"}, obj);
        CHECK(result.first);
        CHECK(result.second == obj);
    }

    {
        auto const result = objectFromAddress(Address{""}, obj);
        CHECK(result.first);
        CHECK(result.second == obj);
    }

    {
        Address address("/abc/def/");
        auto const result = objectFromAddress(address, obj);
        CHECK(result.first);
        CHECK(result.second["subsubkey1"].getValue() == "subsubvalue");
        CHECK(result.second == obj["abc"]["def"].getObject());
    }
}
