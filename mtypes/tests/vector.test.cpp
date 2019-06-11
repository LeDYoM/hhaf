#include "catch.hpp"

#include <mtypes/include/vector.hpp>
#include <mtypes/include/types.hpp>

using namespace lib;

TEST_CASE("vector::vector", "[vector]")
{
    SECTION("Default Constructor")
    {
        vector<u32> m;

        CHECK(m.size() == 0);
        CHECK(m.empty());
        CHECK(m.capacity() == 0);
        
        SECTION("Check errorneous operations")
        {
            m.pop_back();
            CHECK(m.size() == 0U);
            CHECK(m.empty());
            CHECK(m.capacity() == 0U);

            m.clear();
            CHECK(m.size() == 0U);
            CHECK(m.empty());
            CHECK(m.capacity() == 0U);
        }
    }

    SECTION("Constructor with reserved")
    {
        vector<s32> m(2U);
        CHECK(m.size() == 0);
        CHECK(m.empty());
        CHECK(m.capacity() == 2U);

        m.push_back(0);
        m.push_back(1);
        CHECK(m.size() == 2U);
        CHECK_FALSE(m.empty());
        CHECK(m.capacity() == 2U);

        CHECK(m[0] == 0);
        CHECK(m[1] == 1);
    }

    SECTION("Iterators constructor")
    {
        const u32 data[] = { 0U, 1U, 2U, 3U, 4U };
        vector<u32> v(data, data + 5);
        CHECK(v.size() == 5U);
        CHECK(v == vector<u32>{0U, 1U, 2U, 3U, 4U});
        CHECK(0U == v[0]);
        CHECK(1U == v[1]);
        CHECK(2U == v[2]);
        CHECK(3U == v[3]);
        CHECK(4U == v[4]);
    }

    SECTION("Initializer list constructor")
    {
        vector<u32> m;
        m = { 1,9,8,7,6,5,4,3,2,0,1 };
        CHECK(m == vector<u32>{ 1, 9, 8, 7, 6, 5, 4, 3, 2, 0, 1 });

        SECTION("Copy and move constructor")
        {
            auto m2(m);
            CHECK(m == m2);
            CHECK(m.size() == m2.size());
            CHECK(m.capacity() == m2.capacity());

            auto m3(std::move(m));
            CHECK(m.empty());
            CHECK(m2 == m3);
        }
    }

    SECTION("Construct from address and size")
    {
        SECTION("With sizeof")
        {
            const u32 arr[] = { 4, 3, 2, 1 };
            vector<u32> v(arr, sizeof(arr) / sizeof(u32));
            CHECK(v.size() == 4U);
        }

        SECTION("With sizeof")
        {
            const u32 arr[] = { 4, 3, 2, 1 };
            vector<u32> v(std::cbegin(arr), std::cend(arr));
            CHECK(v.size() == 4);
        }
    }
}

class A {
public:
    s32 b;
};

inline auto init_vector_shared_pointers_A() {
    vector_shared_pointers<A> test_vector1;
    test_vector1.push_back(msptr<A>(A{ 1 }));
    test_vector1.push_back(msptr<A>(A{ -2 }));
    test_vector1.push_back(msptr<A>(A{ 3 }));
    test_vector1.push_back(msptr<A>(A{ -2 }));
    test_vector1.push_back(msptr<A>(A{ 5 }));
    test_vector1.push_back(msptr<A>(A{ 100 }));
    test_vector1.push_back(msptr<A>(A{ -2 }));
    test_vector1.push_back(msptr<A>(A{ -2 }));
    test_vector1.push_back(msptr<A>(A{ -1 }));
    test_vector1.push_back(msptr<A>(A{ 0 }));
    return test_vector1;
}

TEST_CASE("vector of shared pointers", "[vector]")
{
    SECTION("Move")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10U);

        vector_shared_pointers<A> test_vector2 = std::move(test_vector1);
        CHECK(test_vector1.empty());
        CHECK(test_vector1.capacity() == 0U);

        CHECK(test_vector2.size() == 10U);

        vector_shared_pointers<A> test_vector3;
        test_vector3 = std::move(test_vector2);
        CHECK(test_vector2.empty());
        CHECK(test_vector2.capacity() == 0U);

        CHECK(test_vector3.size() == 10U);
    }

    SECTION("Add move add")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10U);

        vector_shared_pointers<A> test_vector2 = std::move(test_vector1);
        CHECK(test_vector1.empty());
        CHECK(test_vector1.capacity() == 0U);

        CHECK(test_vector2.size() == 10U);

        vector_shared_pointers<A> test_vector3;
        test_vector3 = std::move(test_vector2);
        CHECK(test_vector2.empty());
        CHECK(test_vector2.capacity() == 0U);

        CHECK(test_vector3.size() == 10U);

        test_vector1.push_back(msptr<A>(1));
    }

    SECTION("Remove")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10);

        test_vector1[1] = nullptr;
        test_vector1[5] = nullptr;

        test_vector1.remove_values(nullptr);
        CHECK(test_vector1.size() == 8);

        test_vector1.push_back(nullptr);
        CHECK(test_vector1.size() == 9);
        test_vector1.remove_values(nullptr);
        CHECK(test_vector1.size() == 8);

        SECTION("Remove removed shared pointer")
        {
            sptr<A> temp = msptr<A>(A{42});
            wptr<A> weak = temp;
            test_vector1.push_back(std::move(temp));
            CHECK_FALSE(weak.lock() == nullptr);
            test_vector1.pop_back();
            CHECK(weak.lock() == nullptr);
        }
    }
}
