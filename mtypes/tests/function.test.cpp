#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

using namespace mtps;

TEST_CASE("function::function", "[function]")
{
    function<s32(s32 const)> a;
    CHECK_FALSE(a);
}

TEST_CASE("function::function with lambda", "[function]")
{
    function<s32(s32 const)> b = [](s32 const n) { return n + 1; };
    CHECK(b);

    CHECK(4 == b(3));
}

TEST_CASE("function::operator==() for lambdas", "[function]")
{
    function<s32(s32 const)> a = [](s32 const n) { return n + 1; };
    function<s32(s32 const)> b = [](s32 const n) { return n + 1; };

    // The lambda contains the same code, but the addresses are different
    CHECK_FALSE(a == b);
    CHECK_FALSE(a.equals(b));

    b = a;
    CHECK(a == b);
    CHECK(a.equals(b));
}

struct TestObject
{
    s32 add2(s32 const n)
    {
        return n + 2;
    }

    s32 add3(s32 const n)
    {
        return n + 3;
    }
};

TEST_CASE("function::equals for pointer to members", "[function]")
{
    TestObject a_obj;
    TestObject b_obj;

    {
        auto a = function<s32(s32 const)>(&a_obj, &TestObject::add2);
        auto b = function<s32(s32 const)>(&b_obj, &TestObject::add2);

        // The lambda contains the same code, but the addresses are different
        CHECK_FALSE(a == b);
        CHECK_FALSE(a.equals(b));
        CHECK(a(5) == 7);
        CHECK(b(50) == 52);
    }

    {
        auto a = function<s32(s32 const)>(&a_obj, &TestObject::add2);
        auto b = function<s32(s32 const)>(&a_obj, &TestObject::add2);

        CHECK_FALSE(a == b);
        CHECK(a.equals(b));
        CHECK(a(5) == 7);
        CHECK(b(50) == 52);
    }

    {
        auto a = function<s32(s32 const)>(&a_obj, &TestObject::add2);
        auto b = function<s32(s32 const)>(&a_obj, &TestObject::add3);

        CHECK_FALSE(a == b);
        CHECK_FALSE(a.equals(b));
        CHECK(a(5) == 7);
        CHECK(b(50) == 53);
    }
}

TEST_CASE("make_function", "[function]")
{
    TestObject a_obj;
    TestObject b_obj;

    {
        auto a = make_function(&a_obj, &TestObject::add2);
        auto b = make_function(&b_obj, &TestObject::add2);

        // The lambda contains the same code, but the addresses are different
        CHECK_FALSE(a == b);
        CHECK_FALSE(a.equals(b));
        CHECK(a(5) == 7);
        CHECK(b(50) == 52);
    }

    {
        auto a = make_function(&a_obj, &TestObject::add2);
        auto b = make_function(&a_obj, &TestObject::add2);

        // The lambda contains the same code, but the addresses are different
        CHECK_FALSE(a == b);
        CHECK(a.equals(b));
        CHECK(a(5) == 7);
        CHECK(b(50) == 52);
    }
}

TEST_CASE("function::operator()", "[function]")
{
    function<s32(s32)> a = [](s32 d) { return d + 1; };
    s32 tmp{4};

    s32 tmp2 = a(tmp);
    CHECK(tmp2 == 5);
}
