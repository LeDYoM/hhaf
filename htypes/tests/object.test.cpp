#include "catch.hpp"

#include <htypes/include/object.hpp>

using namespace htps;

TEST_CASE("Object basic values", "[Object][ValueDictionary]")
{
    Object::ValueDictionary bdictionary{{"key1", "value1"}};
    CHECK(bdictionary.data() ==
          Object::ValueDictionary::content{
              Object::ValueDictionary::element("key1", "value1")});
    CHECK_FALSE(bdictionary.add("key1", "asd", false));
}

TEST_CASE("Object create 1", "[Object]")
{
    Object tester{{"subkey", "subValue"}};
    Object obj{{"key1", "value1"}, {"key2", "value2"}};

    CHECK(tester["subkey"] == "subValue");
    CHECK(obj["key1"] == "value1");
    CHECK(obj["key2"] == "value2");
    CHECK_FALSE(obj["key3"].isValid());
    CHECK_FALSE(obj["key1"]["value1"].isValid());
    CHECK(obj.empty_objects());
    CHECK_FALSE(obj.empty_values());
    CHECK_FALSE(obj.empty());
}

TEST_CASE("Object create 2", "[Object]")
{
    // Initialize with initializer list of objects
    Object obj{
        {"key1", {{"subkey1", "subvalue1"}}},
        {"key2", {{"subkey2", "subvalue2"}}},
        {"key3", Object{{"subkey1", Object{{"subsubkey1", "subsubvalue"}}}}}};

    SECTION("Compare")
    {
        Object obj2{obj};
        CHECK(obj == obj2);
        CHECK_FALSE(obj != obj2);

        const Object::Value v{obj["key1"]};
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

    SECTION("Modify")
    {
        auto tmp_iterator1 = obj.acquireObject("key1");
        CHECK(obj["key1"] == *tmp_iterator1);
        CHECK(obj["key1"].getObject() == *tmp_iterator1);
        tmp_iterator1->set("subkey1", "megavalue1");
        CHECK(obj["key1"]["subkey1"] == "megavalue1");

        auto tmp_iterator2 =
            obj.acquireObject("key2")->acquireValue("subkey2");
        CHECK(obj["key2"]["subkey2"] == tmp_iterator2);
        (*tmp_iterator2) = "ultravalue1";
        CHECK(obj["key2"]["subkey2"] == "ultravalue1");

        CHECK(obj["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
        CHECK(obj.size_objects() == 3U);
        CHECK(obj.empty_values());
        CHECK_FALSE(obj.empty_objects());
        CHECK_FALSE(obj.empty());
        CHECK(obj["key3"]["subkey1"].isObject());
    }
}

TEST_CASE("Object create 3", "[Object]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj3{
        {{"key1", {{"subkey1", "subvalue1"}}},
         {"key2", {{"subkey2", "subvalue2"}}},
         {"key3", Object{{"subkey1", Object{{"subsubkey1", "subsubvalue"}}}}}},
        {{"key4", "value4"}}};

    CHECK(obj3["key1"]["subkey1"] == "subvalue1");
    CHECK(obj3["key2"]["subkey2"] == "subvalue2");
    CHECK(obj3["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    CHECK_FALSE(obj3["key4"]["subkey2"] == "subvalue2");
    CHECK(obj3["key4"] == "value4");
    CHECK_FALSE(obj3["adf"].isValid());
    CHECK_FALSE(obj3["adf"] == "");
}

TEST_CASE("Object create 4", "[Object]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj4{
        {{"key1", {{"subkey1", "subvalue1"}}},
         {"key2", {{"subkey2", "subvalue2"}}},
         {"key3", Object{{"subkey1", Object{{"subsubkey1", "subsubvalue"}}}}}},
        {{"key4", "value4"}}};

    CHECK(obj4["key1"]["subkey1"] == "subvalue1");
    CHECK(obj4["key2"]["subkey2"] == "subvalue2");
    CHECK(obj4["key3"]["subkey1"]["subsubkey1"] == "subsubvalue");
    CHECK_FALSE(obj4["key4"]["subkey2"] == "subvalue2");
    CHECK(obj4["key4"] == "value4");
    CHECK_FALSE(obj4["adf"].isValid());
    CHECK_FALSE(obj4["adf"] == "");
}

TEST_CASE("Object: Read array1", "[Object][vector]")
{
    Object obj{{str(Object::arraySeparator) + "0", "value1"},
               {str(Object::arraySeparator) + "1", "value2"}};

    CHECK(obj[0U] == "value1");
    CHECK(obj[1U] == "value2");

    CHECK(obj[str(Object::arraySeparator) + "0"] == "value1");
    CHECK(obj[str(Object::arraySeparator) + "1"] == "value2");
    CHECK_FALSE(obj[str(Object::arraySeparator) + "2"].isValid());
    CHECK_FALSE(obj[2U].isValid());
}

TEST_CASE("Object: Write array1", "[Object][vector]")
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

TEST_CASE("Object: Read array2", "[Object][vector]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj{{{"key1",
                 {{str(Object::arraySeparator) + "0", "subvalue0"},
                  {str(Object::arraySeparator) + "1", "subvalue1"}}},
                {"key2", {{"subkey2", "subvalue2"}}},
                {"key3",
                 Object{{"subkey1",
                         Object{{str(Object::arraySeparator) + "0",
                                 "subsubvalue"}}}}}},
               {{"key4", "value4"}}};

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
    CHECK(obj["key3"]["subkey1"][str(Object::arraySeparator) + "0"] ==
          "subsubvalue");

    CHECK_FALSE(obj["key4"][0U].isValid());
}

TEST_CASE("Object copy", "[Object]")
{
    // Initialize with initializer list of objects and initializer list of
    // properties.
    Object obj{
        {{"key1", {{"subkey1", "subvalue1"}}},
         {"key2", {{"subkey2", "subvalue2"}}},
         {"key3", Object{{"subkey1", Object{{"subsubkey1", "subsubvalue"}}}}}},
        {{"key4", "value4"}}};

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

TEST_CASE("Object with vector", "[Object][vector]")
{
    vector<s32> v = {-1, 1, 3, -3};
    Object obj;

    SECTION("Without property name")
    {
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

            SECTION("Simple2")
            {
                s32 value{0};

                CHECK(obj[0U].as(value));
                CHECK(value == v[0U]);
                CHECK(obj[1U].as(value));
                CHECK(value == v[1U]);
                CHECK(obj[2U].as(value));
                CHECK(value == v[2U]);
                CHECK(obj[3U].as(value));
                CHECK(value == v[3U]);
                CHECK_FALSE(obj[4U].isValid());
            }
        }

        SECTION("Direct")
        {
            obj << v;

            CHECK(obj[0U].as<s32>() == v[0U]);
            CHECK(obj[1U].as<s32>() == v[1U]);
            CHECK(obj[2U].as<s32>() == v[2U]);
            CHECK(obj[3U].as<s32>() == v[3U]);
            CHECK_FALSE(obj[4U].isValid());

            SECTION("Direct with parameter")
            {
                s32 value{0};

                CHECK(obj[0U].as(value));
                CHECK(value == v[0U]);
                CHECK(obj[1U].as(value));
                CHECK(value == v[1U]);
                CHECK(obj[2U].as(value));
                CHECK(value == v[2U]);
                CHECK(obj[3U].as(value));
                CHECK(value == v[3U]);
                CHECK_FALSE(obj[4U].isValid());
            }
        }

        SECTION("More direct with rv vector and float")
        {
            obj << vector<f32>{2.3F, 1.1F};
            CHECK(obj[0U].as<f32>() == 2.3F);
            CHECK(obj[1U].as<f32>() == 1.1F);
            CHECK_FALSE(obj[2U].isValid());

            SECTION("More direct with rv vector and float with parameter")
            {
                float value{};
                CHECK(obj[0U].as(value));
                CHECK(value == 2.3F);
                CHECK(obj[1U].as(value));
                CHECK(value == 1.1F);
                CHECK_FALSE(obj[2U].isValid());
            }
        }
    }

    SECTION("With property name")
    {
        Object inner_object;

        SECTION("Direct")
        {
            obj.set("test_property", v);

            CHECK(obj["test_property"][0U].as<s32>() == v[0U]);
            CHECK(obj["test_property"][1U].as<s32>() == v[1U]);
            CHECK(obj["test_property"][2U].as<s32>() == v[2U]);
            CHECK(obj["test_property"][3U].as<s32>() == v[3U]);
            CHECK_FALSE(obj["test_property"][4U].isValid());
            CHECK_FALSE(obj[0U].isValid());
        }

        SECTION("More direct with rv vector and float")
        {
            obj.set("other_", vector<f32>{2.3F, 1.1F});
            CHECK(obj["other_"][0U].as<f32>() == 2.3F);
            CHECK(obj["other_"][1U].as<f32>() == 1.1F);
            CHECK_FALSE(obj["other_"][2U].isValid());
            CHECK_FALSE(obj[0U].isValid());
        }
    }
}

TEST_CASE("Object with array", "[Object][vector]")
{
    array<s32, 4U> v = {-1, 1, 3, -3};
    Object obj;

    SECTION("Without property name")
    {
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
            obj << v;

            CHECK(obj[0U].as<s32>() == v[0U]);
            CHECK(obj[1U].as<s32>() == v[1U]);
            CHECK(obj[2U].as<s32>() == v[2U]);
            CHECK(obj[3U].as<s32>() == v[3U]);
            CHECK_FALSE(obj[4U].isValid());

            SECTION("Direct with parameter")
            {
                s32 value{0};

                CHECK(obj[0U].as(value));
                CHECK(value == v[0U]);
                CHECK(obj[1U].as(value));
                CHECK(value == v[1U]);
                CHECK(obj[2U].as(value));
                CHECK(value == v[2U]);
                CHECK(obj[3U].as(value));
                CHECK(value == v[3U]);
                CHECK_FALSE(obj[4U].isValid());
            }
        }

        SECTION("More direct with rv array and float")
        {
            obj << array<f32, 2U>{2.3F, 1.1F};
            CHECK(obj[0U].as<f32>() == 2.3F);
            CHECK(obj[1U].as<f32>() == 1.1F);

            SECTION("More direct with rv array and float with parameter")
            {
                float value{};
                CHECK(obj[0U].as(value));
                CHECK(value == 2.3F);
                CHECK(obj[1U].as(value));
                CHECK(value == 1.1F);
                CHECK_FALSE(obj[2U].isValid());
            }
        }
    }

    SECTION("With property name")
    {
        Object inner_object;

        SECTION("Direct")
        {
            obj.set("test_property", v);

            CHECK(obj["test_property"][0U].as<s32>() == v[0U]);
            CHECK(obj["test_property"][1U].as<s32>() == v[1U]);
            CHECK(obj["test_property"][2U].as<s32>() == v[2U]);
            CHECK(obj["test_property"][3U].as<s32>() == v[3U]);
            CHECK_FALSE(obj["test_property"][4U].isValid());
            CHECK_FALSE(obj[0U].isValid());

            SECTION("Direct with parameter")
            {
                s32 value{0};

                CHECK(obj["test_property"][0U].as(value));
                CHECK(value == v[0U]);
                CHECK(obj["test_property"][1U].as(value));
                CHECK(value == v[1U]);
                CHECK(obj["test_property"][2U].as(value));
                CHECK(value == v[2U]);
                CHECK(obj["test_property"][3U].as(value));
                CHECK(value == v[3U]);
                CHECK_FALSE(obj["test_property"][4U].isValid());
                CHECK_FALSE(obj[0U].isValid());
            }
        }

        SECTION("More direct with rv vector and float")
        {
            obj.set("other_", vector<f32>{2.3F, 1.1F});
            CHECK(obj["other_"][0U].as<f32>() == 2.3F);
            CHECK(obj["other_"][1U].as<f32>() == 1.1F);
            CHECK_FALSE(obj["other_"][2U].isValid());
            CHECK_FALSE(obj[0U].isValid());
        }
    }
}

namespace TestVectorWithCustomTypes
{
struct Simple
{
    int a;
    short b;
    long c;

    constexpr Simple() noexcept : a{}, b{}, c{} {}
    constexpr Simple(int a_, short b_, long c_) noexcept : a{a_}, b{b_}, c{c_}
    {}

    bool operator==(const Simple& rhs) const
    {
        return ((a == rhs.a) && (b == rhs.b) && (c == rhs.c));
    }
};

inline const Object& operator>>(const Object& obj, Simple& data)
{
    data.a = obj["a"].as<int>();
    data.b = obj["b"].as<short>();
    data.c = obj["c"].as<long>();
    return obj;
}

inline Object& operator<<(Object& obj, const Simple& data)
{
    obj.set("a", data.a);
    obj.set("b", data.b);
    obj.set("c", data.c);
    return obj;
}
}  // namespace TestVectorWithCustomTypes

TEST_CASE("Object with vector of custom types", "[Object][vector]")
{
    using namespace TestVectorWithCustomTypes;

    vector<Simple> vec = {{5000, 40, 10000}, {1000, 10, 20000}};

    Object obj;
    obj << vec;

    CHECK(obj[0U]["a"].as<int>() == vec[0U].a);
    CHECK(obj[0U]["b"].as<short>() == vec[0U].b);
    CHECK(obj[0U]["c"].as<long>() == vec[0U].c);
    CHECK(obj[0U].getObject().empty_objects());
    CHECK(obj[0U].getObject().size_values() == 3U);

    CHECK(obj[1U]["a"].as<int>() == vec[1U].a);
    CHECK(obj[1U]["b"].as<short>() == vec[1U].b);
    CHECK(obj[1U]["c"].as<long>() == vec[1U].c);
    CHECK(obj[1U].getObject().empty_objects());
    CHECK(obj[1U].getObject().size_values() == 3U);

    CHECK(obj.size_objects() == 2U);
    CHECK(obj.empty_values());

    vector<Simple> output;
    obj >> output;

    CHECK(vec == output);

    SECTION("As with parameter and custom types")
    {
        int a{};
        short b{};
        long c{};

        CHECK(obj[0U]["a"].as(a));
        CHECK(a == vec[0U].a);
        CHECK(obj[0U]["b"].as(b));
        CHECK(b == vec[0U].b);
        CHECK(obj[0U]["c"].as(c));
        CHECK(c == vec[0U].c);
    }
}

namespace TestVectorWithCustomTypesEnumsAndFloats
{
enum class MySmallEnum : u8
{
    First,
    Second
};

enum class MyDefaultEnum
{
    First,
    Second
};

enum class MyBigEnum : u64
{
    First,
    Second
};

struct Simple
{
    MySmallEnum small_enum{MySmallEnum::First};
    MyDefaultEnum default_enum{MyDefaultEnum::First};
    MyBigEnum big_enum{MyBigEnum::First};
    f32 a{};
    f64 b{};

//    Simple() noexcept = default;

    bool operator==(const Simple& rhs) const
    {
        return ((small_enum == rhs.small_enum) &&
                (default_enum == rhs.default_enum) &&
                (big_enum == rhs.big_enum) && (a == rhs.a) && (b == rhs.b));
    }
};

inline const Object& operator>>(const Object& obj, Simple& data)
{
    data.a            = obj["a"].as<f32>();
    data.b            = obj["b"].as<f64>();
    data.small_enum   = obj["small_enum"].as<MySmallEnum>();
    data.default_enum = obj["default_enum"].as<MyDefaultEnum>();
    data.big_enum     = obj["big_enum"].as<MyBigEnum>();

    return obj;
}

inline Object& operator<<(Object& obj, const Simple& data)
{
    obj.set("a", data.a);
    obj.set("b", data.b);
    obj.set("small_enum", data.small_enum);
    obj.set("default_enum", data.default_enum);
    obj.set("big_enum", data.big_enum);
    return obj;
}

}  // namespace TestVectorWithCustomTypesEnumsAndFloats

TEST_CASE("Object with vector of custom type sand enums and floats",
          "[Object][vector]")
{
    using namespace TestVectorWithCustomTypesEnumsAndFloats;

    vector<Simple> vec = {{MySmallEnum::First, MyDefaultEnum::First,
                           MyBigEnum::First, 4.5F, 2000.123},
                          {MySmallEnum::Second, MyDefaultEnum::Second,
                           MyBigEnum::Second, -1.2F, -454341.999999}};

    Object obj;
    obj << vec;

    SECTION("as<>() without parameter")
    {
        CHECK(obj[0U]["a"].as<f32>() == vec[0U].a);
        CHECK(obj[0U]["b"].as<f64>() == vec[0U].b);
        CHECK(obj[0U]["small_enum"].as<MySmallEnum>() == vec[0U].small_enum);
        CHECK(obj[0U]["default_enum"].as<MyDefaultEnum>() ==
              vec[0U].default_enum);
        CHECK(obj[0U]["big_enum"].as<MyBigEnum>() == vec[0U].big_enum);
        CHECK(obj[0U].getObject().empty_objects());
        CHECK(obj[0U].getObject().size_values() == 5U);

        CHECK(obj[1U]["a"].as<f32>() == vec[1U].a);
        CHECK(obj[1U]["b"].as<f64>() == vec[1U].b);
        CHECK(obj[1U]["small_enum"].as<MySmallEnum>() == vec[1U].small_enum);
        CHECK(obj[1U]["default_enum"].as<MyDefaultEnum>() ==
              vec[1U].default_enum);
        CHECK(obj[1U]["big_enum"].as<MyBigEnum>() == vec[1U].big_enum);
        CHECK(obj[1U].getObject().empty_objects());
        CHECK(obj[1U].getObject().size_values() == 5U);

        CHECK(obj.size_objects() == 2U);
        CHECK(obj.empty_values());
    }

    SECTION("as<>(T&) with parameters")
    {
        f32 a{};
        f64 b{};
        MySmallEnum my_small_enum;
        MyDefaultEnum my_default_enum;
        MyBigEnum my_big_enum;

        CHECK(obj[0U]["a"].as(a));
        CHECK(a == vec[0U].a);
        CHECK(obj[0U]["b"].as(b));
        CHECK(b == vec[0U].b);
        CHECK(obj[0U]["small_enum"].as(my_small_enum));
        CHECK(my_small_enum == vec[0U].small_enum);
        CHECK(obj[0U]["default_enum"].as(my_default_enum));
        CHECK(my_default_enum == vec[0U].default_enum);
        CHECK(obj[0U]["big_enum"].as(my_big_enum));
        CHECK(my_big_enum == vec[0U].big_enum);

        CHECK(obj[0U].getObject().empty_objects());
        CHECK(obj[0U].getObject().size_values() == 5U);

        CHECK(obj[1U]["a"].as(a));
        CHECK(a == vec[1U].a);
        CHECK(obj[1U]["b"].as(b));
        CHECK(b == vec[1U].b);
        CHECK(obj[1U]["small_enum"].as(my_small_enum));
        CHECK(my_small_enum == vec[1U].small_enum);
        CHECK(obj[1U]["default_enum"].as(my_default_enum));
        CHECK(my_default_enum == vec[1U].default_enum);
        CHECK(obj[1U]["big_enum"].as(my_big_enum));
        CHECK(my_big_enum == vec[1U].big_enum);
        CHECK(obj[1U].getObject().empty_objects());
        CHECK(obj[1U].getObject().size_values() == 5U);
    }

    vector<Simple> output;
    obj >> output;

    CHECK(vec == output);
}

TEST_CASE("Object with array of custom types and enums and floats",
          "[Object][vector]")
{
    using namespace TestVectorWithCustomTypesEnumsAndFloats;

    array<Simple, 2U> vec = {{MySmallEnum::First, MyDefaultEnum::First,
                              MyBigEnum::First, 4.5F, 2000.123},
                             {MySmallEnum::Second, MyDefaultEnum::Second,
                              MyBigEnum::Second, -1.2F, -454341.999999}};

    Object obj;
    obj << vec;

    CHECK(obj[0U]["a"].as<f32>() == vec[0U].a);
    CHECK(obj[0U]["b"].as<f64>() == vec[0U].b);
    CHECK(obj[0U]["small_enum"].as<MySmallEnum>() == vec[0U].small_enum);
    CHECK(obj[0U]["default_enum"].as<MyDefaultEnum>() == vec[0U].default_enum);
    CHECK(obj[0U]["big_enum"].as<MyBigEnum>() == vec[0U].big_enum);
    CHECK(obj[0U].getObject().empty_objects());
    CHECK(obj[0U].getObject().size_values() == 5U);

    CHECK(obj[1U]["a"].as<f32>() == vec[1U].a);
    CHECK(obj[1U]["b"].as<f64>() == vec[1U].b);
    CHECK(obj[1U]["small_enum"].as<MySmallEnum>() == vec[1U].small_enum);
    CHECK(obj[1U]["default_enum"].as<MyDefaultEnum>() == vec[1U].default_enum);
    CHECK(obj[1U]["big_enum"].as<MyBigEnum>() == vec[1U].big_enum);
    CHECK(obj[1U].getObject().empty_objects());
    CHECK(obj[1U].getObject().size_values() == 5U);

    CHECK(obj.size_objects() == 2U);
    CHECK(obj.empty_values());

    array<Simple, 2U> output;
    obj >> output;

    CHECK(vec == output);
}
