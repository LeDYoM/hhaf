#include "catch.hpp"

#include <mtypes/include/dicty.hpp>

using namespace lib;

TEST_CASE("Dicty basic values", "[dicty][ValueDictionary]")
{
    Object::ValueDictionary bdictionary{ {"key1", "value1"} };
    CHECK(bdictionary.data() == Object::ValueDictionary::content{ Object::ValueDictionary::element("key1", "value1") });
    CHECK_FALSE(bdictionary.add("key1", "asd", false));
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
    CHECK(obj.empty_objects());
    CHECK_FALSE(obj.empty_values());
    CHECK_FALSE(obj.empty());
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

    SECTION("Compare")
    {
        Object obj2{ obj };
        CHECK(obj == obj2);
        CHECK_FALSE(obj != obj2);

        const Object::Value v{ obj["key1"] };
        CHECK(v == obj2["key1"]);
        CHECK_FALSE(v != obj2["key1"]);
    }

    CHECK(obj["key1"]["subkey1"] == "subvalue1");
    CHECK(obj["key2"]["subkey2"] == "subvalue2");
    CHECK(obj["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    CHECK(obj.size_objects() == 3U);
    CHECK(obj.empty_values());
    CHECK_FALSE(obj.empty_objects());
    CHECK_FALSE(obj.empty());
    CHECK(obj["key3"]["subkey1"].isObject());
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

TEST_CASE("dicty create 4","[dicty]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj4
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
                Object{ { "subkey1",
                    Object{
                        { "subsubkey1", "subsubvalue" }
                    }
                }
            }
        }
        },
        {
            { "key4","value4" }
        }
    };

    CHECK(obj4["key1"]["subkey1"] == "subvalue1");
    CHECK(obj4["key2"]["subkey2"] == "subvalue2");
    CHECK(obj4["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    CHECK_FALSE(obj4["key4"]["subkey2"] == "subvalue2");
    CHECK(obj4["key4"] == "value4");
    CHECK_FALSE(obj4["adf"].isValid());
    CHECK_FALSE(obj4["adf"] == "");
}

TEST_CASE("Dicty: Read array1", "[dicty][vector]")
{
    Object obj{
        {str(Object::arraySeparator) + "0", "value1"},
        {str(Object::arraySeparator) + "1", "value2"}
    };

    CHECK(obj[0U] == "value1");
    CHECK(obj[1U] == "value2");

    CHECK(obj[str(Object::arraySeparator) + "0"] == "value1");
    CHECK(obj[str(Object::arraySeparator) + "1"] == "value2");
    CHECK_FALSE(obj[str(Object::arraySeparator) + "2"].isValid());
    CHECK_FALSE(obj[2U].isValid());
}

TEST_CASE("Dicty: Write array1", "[dicty][vector]")
{
    Object obj;
    obj.set(0U, "value1");
    obj.set(1U, "value2");
    obj.set(2U, 12345UL);
    obj.set(3U, 1.2);
    obj.set(4U, static_cast<s32>(32));

    CHECK(obj[0U] == "value1");
    CHECK(obj[1U] == "value2");
    CHECK(obj[2U].as<u32>() == 12345UL);
    CHECK(obj[3U].as<f64>() == 1.2);
    CHECK(obj[4U].as<s32>() == 32);

    CHECK(obj[str(Object::arraySeparator) + "0"] == "value1");
    CHECK(obj[str(Object::arraySeparator) + "1"] == "value2");
    CHECK(obj[str(Object::arraySeparator) + "2"].as<u32>() == 12345UL);
    CHECK(obj[str(Object::arraySeparator) + "3"].as<f64>() == 1.2);
    CHECK(obj[str(Object::arraySeparator) + "4"].as<s32>() == 32);

    CHECK_FALSE(obj[5U].isValid());
}

TEST_CASE("Dicty: Read array2", "[dicty][vector]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj
    {
        {
            { "key1",
                {
                    { str(Object::arraySeparator) + "0", "subvalue0" },
                    { str(Object::arraySeparator) + "1", "subvalue1" }
                }
            },
            { "key2",
                {
                    { "subkey2", "subvalue2" }
                }
            },
            { "key3",
                Object{ { "subkey1",
                    Object{
                        { str(Object::arraySeparator) + "0", "subsubvalue" }
                    }
                }
            }
        }
        },
        {
            { "key4","value4" }
        }
    };

    CHECK(obj["key1"][0U] == "subvalue0");
    CHECK(obj["key1"][1U] == "subvalue1");
    CHECK_FALSE(obj["key1"][2U].isValid());

    // The construction [str(Object::arraySeparator) + "Number"] is not really
    // meant to be used, but here it is used to ensure arrays might also be
    // read this way.
    CHECK(obj["key1"][str(Object::arraySeparator) + "0"] == "subvalue0");
    CHECK(obj["key1"][str(Object::arraySeparator) + "1"] == "subvalue1");

    CHECK_FALSE(obj["key2"][0U].isValid());

    CHECK(obj["key3"]["subkey1"][0U] == "subsubvalue");
    CHECK(obj["key3"]["subkey1"][str(Object::arraySeparator) + "0"] == "subsubvalue");

    CHECK_FALSE(obj["key4"][0U].isValid());
}

TEST_CASE("dicty copy", "[dicty]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj
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

    SECTION("Copy values")
    {
        Object obj2;

        CHECK(obj2.set("other_key1", obj["key1"]["subkey1"]));
        CHECK(obj2["other_key1"] == "subvalue1");

        CHECK(obj2.set("other_key2", obj["key2"]["subkey2"]));
        CHECK(obj2["other_key2"] == "subvalue2");

        CHECK(obj2.set("other_key3", obj["key3"]["subkey1"]["subsubkey1"]));
        CHECK(obj2["other_key3"] == "subsubvalue");

        CHECK(obj2.set("other_key4", obj["key4"]));
        CHECK(obj2["other_key4"] == "value4");

        CHECK_FALSE(obj2.set("other_invalid_key", obj["invalid_key"]));
        CHECK_FALSE(obj2["other_invalid_key"].isValid());

        // Ensure that the object is copied, not just linked.
        obj2.set("other_key1", "other_value");
        CHECK(obj["key1"]["subkey1"] == "subvalue1");
        CHECK(obj2["other_key1"] == "other_value");

    }

    SECTION("Copy objects")
    {
        Object obj2;

        CHECK(obj2.set("other_key1", obj["key1"]));
        CHECK(obj2["other_key1"]["subkey1"] == "subvalue1");

        CHECK(obj2.set("other_key2", obj["key2"]));
        CHECK(obj2["other_key2"]["subkey2"] == "subvalue2");

        CHECK(obj2.set("other_key3", obj["key3"]));
        CHECK(obj2["other_key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    }
}

TEST_CASE("dicty with vector", "[dicty][vector]")
{
    vector<s32> v = {-1, 1, 3, -3};
    Object obj;

    SECTION("Simple")
    {
        obj.set(0U, v[0U]);
        obj.set(1U, v[1U]);
        obj.set(2U, v[2U]);
        obj.set(3U, v[3U]);

        CHECK(obj[0U].as<s32>() == v[0U]);
        CHECK(obj[1U].as<s32>() == v[1U]);
        CHECK(obj[2U].as<s32>() == v[2U]);
        CHECK(obj[3U].as<s32>() == v[3U]);
        CHECK_FALSE(obj[4U].isValid());
    }

    SECTION("Direct")
    {
        obj.set(v);

        CHECK(obj[0U].as<s32>() == v[0U]);
        CHECK(obj[1U].as<s32>() == v[1U]);
        CHECK(obj[2U].as<s32>() == v[2U]);
        CHECK(obj[3U].as<s32>() == v[3U]);
        CHECK_FALSE(obj[4U].isValid());
    }

    SECTION("More direct with rv vector and float")
    {
        obj.set(vector<f32>{2.3F, 1.1F});
        CHECK(obj[0U].as<f32>() == 2.3F);
        CHECK(obj[1U].as<f32>() == 1.1F);
    }
}
