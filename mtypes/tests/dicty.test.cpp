#include "catch.hpp"

#include <mtypes/include/dicty.hpp>

using namespace lib;
using namespace lib::dicty;

TEST_CASE("basic values", "[dicty]")
{
    Object::ValueDictionary bdictionary{ {"key1", "value1"} };
    CHECK(bdictionary.data() == Object::ValueDictionary::content{ Object::ValueDictionary::element("key1", "value1")});
    CHECK_FALSE(bdictionary.add("key1", "asd",false));
}

TEST_CASE("dicty create 1", "[dicty]")
{
    Object tester{ {"subkey","subValue"} };
    Object obj{
        {"key1", "value1"},
        {"key2", "value2"}
    };

    CHECK(tester["subkey"] == "subValue");
    CHECK(obj["key1"] == "value1");
    CHECK(obj["key2"] == "value2");
    CHECK_FALSE(obj["key3"].isValid());
    CHECK_FALSE(obj["key1"]["value1"].isValid());
}

TEST_CASE("dicty create 2", "[dicty]")
{
    // Initialize with initializer list of objects
    Object obj
    {
        { "key1",
            {
                { "subkey1", "subvalue1" }
            }
        },
        { "key2",
            {
                { "subkey2", "subvalue2" }
            }
        },
        { "key3",
            Object{ {"subkey1",
                Object {
                    { "subsubkey1", "subsubvalue" }
                }
            } }
        }
    };

    CHECK(obj["key1"]["subkey1"] == "subvalue1");
    CHECK(obj["key2"]["subkey2"] == "subvalue2");
    CHECK(obj["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
}

TEST_CASE("dicty create 3", "[dicty]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj3
    {
        {
            { "key1",
                {
                    { "subkey1", "subvalue1" }
                }
            },
            { "key2",
                {
                    { "subkey2", "subvalue2" }
                }
            },
            { "key3",
                Object{ {"subkey1",
                    Object {
                        { "subsubkey1", "subsubvalue" }
                    }
                } }
            }
        },
        {
            {"key4","value4"}
        }
    };

    CHECK(obj3["key1"]["subkey1"] == "subvalue1");
    CHECK(obj3["key2"]["subkey2"] == "subvalue2");
    CHECK(obj3["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    CHECK_FALSE(obj3["key4"]["subkey2"] == "subvalue2");
    CHECK(obj3["key4"] == "value4");
    CHECK_FALSE(obj3["adf"].isValid());
    CHECK_FALSE(obj3["adf"] == "");
}
