#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/include/object_factory.hpp>

#include <typeinfo>
#include <typeindex>

using namespace mtps;
using namespace lib;
using namespace lib::scene;

namespace
{
auto createUptrInt(int d)
{
    return muptr<int>(d + 1);
}
} // namespace

TEST_CASE("ObjectFactory simple case", "[hef][ObjectFactory]")
{
    ObjectFactory<int, int> a;

    CHECK(a.empty());
    CHECK(a.size() == 0U);

    CHECK(a.registerObjectType<int>(mtps::str{"obj1"}));

    CHECK_FALSE(a.empty());
    CHECK(a.size() == 1U);

    auto t = a.create("obj1", 5);
    CHECK(*t == 5);

    // t is a normal uptr<int>
    CHECK(++(*t) == 6);

    SECTION("Invalid object")
    {
        // Test a not existent object
        auto t2 = a.create("obj2", 5);
        CHECK(t2 == nullptr);
    }

    SECTION("Register with function")
    {
        CHECK(a.registerObjectType("obj2", createUptrInt));
        CHECK(a.size() == 2);

        SECTION("Create with function")
        {
            auto t = a.create("obj2", 10);
            CHECK(*t == 11);
        }
    }
}

namespace
{
class NoStaticTypeName
{
public:
    NoStaticTypeName(int data) : data_{data} {}
    int data() const { return data_; }

    NoStaticTypeName &operator++()
    {
        ++data_;
        return *this;
    }

private:
    int data_;
};
} // namespace

TEST_CASE("ObjectFactory type no static name simple case", "[hef][ObjectFactory]")
{
    ObjectFactory<NoStaticTypeName, int> a;

    CHECK(a.empty());
    CHECK(a.size() == 0U);

    CHECK(a.registerObjectType<NoStaticTypeName>(mtps::str{"NoStaticTypeName1"}));

    CHECK_FALSE(a.empty());
    CHECK(a.size() == 1U);

    auto t = a.create("NoStaticTypeName1", 5);
    CHECK((*t).data() == 5);

    // t is a normal uptr<int>
    CHECK((++(*t)).data() == 6);

    SECTION("Invalid object")
    {
        // Test a not existent object
        auto t2 = a.create("obj2", 5);
        CHECK(t2 == nullptr);
    }
}

namespace
{
class Interface
{
public:
    virtual ~Interface() {}
    virtual int data() const noexcept = 0;
};

class ObjectImpl1 : public Interface
{
public:
    static constexpr char StaticTypeName[] = "ObjectImpl1";

    ObjectImpl1(const str &data)
        : t_{data == "" ? 0 : 1} {}

    int data() const noexcept override
    {
        return t_ + 3;
    }

private:
    int t_;
};

class ObjectImpl2 : public Interface
{
public:
    static constexpr char StaticTypeName[] = "ObjectImpl2";

    ObjectImpl2(const str &data)
        : t_{data == "" ? 0 : 1} {}

    int data() const noexcept override
    {
        return t_ + 10;
    }

private:
    int t_;
};

} // namespace

TEST_CASE("ObjectFactory type with interface and different concrete types",
          "[hef][ObjectFactory]")
{
    ObjectFactory<Interface, str> a;

    CHECK(a.empty());
    CHECK(a.size() == 0U);

    CHECK(a.registerObjectType<ObjectImpl1>(str{"MyObjectImpl1"}));
    CHECK(a.registerObjectType<ObjectImpl2>(str{"MyObjectImpl2"}));

    // Check double registering fails
    CHECK_FALSE(a.registerObjectType<ObjectImpl2>(str{"MyObjectImpl1"}));
    CHECK_FALSE(a.registerObjectType<ObjectImpl1>(str{"MyObjectImpl1"}));

    CHECK_FALSE(a.empty());
    CHECK(a.size() == 2U);

    auto t = a.create("MyObjectImpl1", "test");
    CHECK((*t).data() == 4);

    // t is an interface so is valid for different concrete types
    t = a.create("MyObjectImpl2", "other");
    CHECK((*t).data() == 11);

    SECTION("Invalid object")
    {
        // Test a not existent object
        t = a.create("obj2", "abc");
        CHECK(t == nullptr);
    }

    SECTION("Automatic registering")
    {
        CHECK(a.registerObjectType<ObjectImpl1>());
        CHECK(a.registerObjectType<ObjectImpl2>());

        CHECK_FALSE(a.empty());
        CHECK(a.size() == 4U);
        auto t_obj = a.create<ObjectImpl1>("test");
        auto t_obj2 = a.create<ObjectImpl2>("");

        // Both objects have the same type
        CHECK(std::type_index(typeid(t_obj)) == std::type_index(typeid(t_obj2)));

        // But they are different objects
        CHECK_FALSE(t_obj->data() == t_obj2->data());
        CHECK(t_obj->data() == 4);
        CHECK(t_obj2->data() == 10);
    }
}
