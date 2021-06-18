#include "catch.hpp"

#include <htypes/include/vector.hpp>
#include <htypes/include/types.hpp>

using namespace htps;

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

            SECTION("Copy empty")
            {
                vector_shared_pointers<s32> empty_vector;
                CHECK(empty_vector.capacity() == 0U);
                CHECK(empty_vector.size() == 0U);

                vector_shared_pointers<s32> copy_empty(empty_vector);
                CHECK(copy_empty.capacity() == 0U);
                CHECK(copy_empty.size() == 0U);
            }
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

    SECTION("Copy constructor")
    {
        vector<s32> m;

        m.push_back(5);

        vector<s32> m2(m);
        CHECK(m.size() == m2.size());

        m.reserve(10U);
        CHECK(m.size() == 1U);

        vector<s32> m3(m);
        CHECK(m3.capacity() <= m.capacity());
        CHECK(m3.size() <= m.size());
        CHECK(m3[0U] == 5);
    }

    SECTION("Iterators constructor")
    {
        const u32 data[] = {0U, 1U, 2U, 3U, 4U};
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
        m = {1, 9, 8, 7, 6, 5, 4, 3, 2, 0, 1};
        CHECK(m == vector<u32>{1, 9, 8, 7, 6, 5, 4, 3, 2, 0, 1});

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
            const u32 arr[] = {4, 3, 2, 1};
            vector<u32> v(arr, sizeof(arr) / sizeof(u32));
            CHECK(v.size() == 4U);
        }

        SECTION("With sizeof")
        {
            const u32 arr[] = {4, 3, 2, 1};
            vector<u32> v(std::cbegin(arr), std::cend(arr));
            CHECK(v.size() == 4U);
        }
    }

    SECTION("Emplace")
    {
        vector<u32> v;

        v.emplace_back(0);
        CHECK(v.size() == 1U);
        v.pop_back();
        CHECK(v.empty());
    }
}

class A
{
public:
    s32 b;
};

inline auto init_vector_shared_pointers_A()
{
    vector_shared_pointers<A> test_vector1;
    test_vector1.push_back(msptr<A>(A{1}));
    test_vector1.push_back(msptr<A>(A{-2}));
    test_vector1.push_back(msptr<A>(A{3}));
    test_vector1.push_back(msptr<A>(A{-2}));
    test_vector1.push_back(msptr<A>(A{5}));
    test_vector1.push_back(msptr<A>(A{100}));
    test_vector1.push_back(msptr<A>(A{-2}));
    test_vector1.push_back(msptr<A>(A{-2}));
    test_vector1.push_back(msptr<A>(A{-1}));
    test_vector1.push_back(msptr<A>(A{0}));
    return test_vector1;
}

TEST_CASE("vector of shared pointers", "[vector]")
{
    SECTION("Copy empty")
    {
        vector_shared_pointers<A> empty_vector;
        CHECK(empty_vector.capacity() == 0U);
        CHECK(empty_vector.size() == 0U);

        vector_shared_pointers<A> copy_empty(empty_vector);
        CHECK(copy_empty.capacity() == 0U);
        CHECK(copy_empty.size() == 0U);
    }

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

        test_vector1.push_back(msptr<A>(A{1}));
    }

    SECTION("Remove")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10U);

        test_vector1[1] = nullptr;
        test_vector1[5] = nullptr;

        test_vector1.erase_values(nullptr);
        CHECK(test_vector1.size() == 8U);

        test_vector1.push_back(nullptr);
        CHECK(test_vector1.size() == 9U);
        test_vector1.erase_values(nullptr);
        CHECK(test_vector1.size() == 8U);

        SECTION("erase_one_index")
        {
            test_vector1.emplace_back(msptr<A>(A{50}));
            test_vector1.emplace_back(msptr<A>(A{51}));
            CHECK(test_vector1.size() == 10U);

            {
                auto const result = test_vector1.erase_one_index(8U);
                CHECK(test_vector1.size() == 9U);
                CHECK((*result)->b == 51);
            }

            {
                auto const result = test_vector1.erase_one_index(9U);
                CHECK(result == test_vector1.end());
            }
        }

        SECTION("erase_one keep order")
        {
            test_vector1.emplace_back(msptr<A>(A{50}));
            test_vector1.emplace_back(msptr<A>(A{51}));
            CHECK(test_vector1.size() == 10U);

            {
                auto const iterator = test_vector1.begin();
                auto const value2   = (test_vector1[1U]->b);
                auto const value_last =
                    (test_vector1[test_vector1.size() - 1U]->b);

                CHECK(std::next(iterator) == &(test_vector1[1U]));
                test_vector1.erase_one<false>(*test_vector1.begin());
                CHECK(test_vector1[0U]->b == value2);
                CHECK((test_vector1[test_vector1.size() - 1U]->b) ==
                      value_last);
            }
        }

        SECTION("Remove removed shared pointer")
        {
            sptr<A> temp = msptr<A>(A{42});
            wptr<A> weak = temp;
            test_vector1.push_back(std::move(temp));
            CHECK(test_vector1.size() == 9U);
            CHECK_FALSE(weak.lock() == nullptr);
            test_vector1.pop_back();
            CHECK(test_vector1.size() == 8U);
            CHECK(weak.lock() == nullptr);
        }

        SECTION("Remove if")
        {
            sptr<A> temp = msptr<A>(A{42});
            wptr<A> weak = temp;
            test_vector1.push_back(std::move(temp));
            CHECK(test_vector1.size() == 9U);
            CHECK_FALSE(weak.lock() == nullptr);
            test_vector1.erase_if(
                [](const sptr<A> element) { return element->b == 42; });
            CHECK(test_vector1.size() == 8U);
            CHECK(weak.lock() == nullptr);
        }
    }

    SECTION("Emplace")
    {
        vector_shared_pointers<A> test_vector;
        sptr<A> temp = msptr<A>(A{42});

        test_vector.emplace_back(new A{42});
        CHECK(test_vector.size() == 1U);
        test_vector.pop_back();
        CHECK(test_vector.empty());
    }

    SECTION("Clear")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10U);

        sptr<A> temp = msptr<A>(A{42});
        wptr<A> weak = temp;
        test_vector1.push_back(std::move(temp));
        CHECK_FALSE(weak.lock() == nullptr);
        test_vector1.clear();
        CHECK(weak.lock() == nullptr);
    }

    SECTION("shrink_to_fit")
    {
        vector_shared_pointers<A> test_vector1(init_vector_shared_pointers_A());
        CHECK(test_vector1.size() == 10U);
        CHECK(test_vector1.capacity() >= 10U);

        test_vector1.pop_back();
        test_vector1.pop_back();
        CHECK(test_vector1.size() == 8U);
        CHECK(test_vector1.capacity() >= 10U);

        test_vector1.shrink_to_fit();
        CHECK(test_vector1.size() == 8U);
        CHECK(test_vector1.capacity() == 8U);

        test_vector1.clear();
        CHECK(test_vector1.size() == 0U);
        CHECK(test_vector1.capacity() == 8U);

        test_vector1.shrink_to_fit();
        CHECK(test_vector1.size() == 0U);
        CHECK(test_vector1.capacity() == 0U);
    }
}

TEST_CASE("Unique ptr")
{
    vector_unique_pointers<s32> test_vector1;
    vector_unique_pointers<s32> test_vector2(4U);

    CHECK(test_vector1.capacity() == 0U);
    CHECK(test_vector2.capacity() == 4U);

    test_vector1.push_back(muptr<s32>(1));
    test_vector2.push_back(muptr<s32>(1));

    CHECK((*test_vector1[0U]) == (*test_vector2[0U]));

    test_vector1.emplace_back(muptr<s32>(2));
    test_vector2.emplace_back(muptr<s32>(2));

    CHECK((*test_vector1[1U]) == (*test_vector2[1U]));

    test_vector1.shrink_to_fit();
    test_vector2.shrink_to_fit();

    CHECK(test_vector1.capacity() == 2U);
    CHECK(test_vector1.capacity() == 2U);

    test_vector1.clear();
    test_vector2.clear();

    test_vector1.shrink_to_fit();
    test_vector2.shrink_to_fit();

    CHECK(test_vector1.capacity() == 0U);
    CHECK(test_vector1.capacity() == 0U);

    test_vector1.shrink_to_fit();
    test_vector2.shrink_to_fit();

    CHECK(test_vector1.capacity() == 0U);
    CHECK(test_vector1.capacity() == 0U);
}

TEST_CASE("Grow policy")
{
    vector<s32> default_test_vector;
    vector_storage<s32, AllocatorType<s32>, GrowPolicyDouble>
        double_grow_test_vector;

    CHECK(default_test_vector.empty());
    CHECK(default_test_vector.capacity() == 0U);

    CHECK(double_grow_test_vector.empty());
    CHECK(double_grow_test_vector.capacity() == 0U);

    default_test_vector.push_back(1);
    double_grow_test_vector.push_back(1);

    CHECK(default_test_vector.size() == 1U);
    CHECK(default_test_vector.capacity() == 1U);

    CHECK(double_grow_test_vector.size() == 1U);
    CHECK(double_grow_test_vector.capacity() == 1U);

    default_test_vector.push_back(2);
    double_grow_test_vector.push_back(2);

    CHECK(default_test_vector.size() == 2U);
    CHECK(default_test_vector.capacity() == 2U);

    CHECK(double_grow_test_vector.size() == 2U);
    CHECK(double_grow_test_vector.capacity() == 2U);

    default_test_vector.push_back(3);
    double_grow_test_vector.push_back(3);

    CHECK(default_test_vector.size() == 3U);
    CHECK(default_test_vector.capacity() == 3U);

    CHECK(double_grow_test_vector.size() == 3U);
    CHECK(double_grow_test_vector.capacity() == 4U);
}

struct MoveOnly
{
public:
    explicit MoveOnly(int b) : a{b} {}
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;

    MoveOnly(MoveOnly&&) noexcept = default;
    MoveOnly& operator=(MoveOnly&&) = default;
    int get() const noexcept { return a; }
private:
    int a;
};

TEST_CASE("Movable only objects")
{
    static_assert(!std::is_copy_constructible_v<MoveOnly>);
    static_assert(!std::is_copy_assignable_v<MoveOnly>);

    static_assert(std::is_move_constructible_v<MoveOnly>);
    static_assert(std::is_move_assignable_v<MoveOnly>);

    vector<MoveOnly> v;
    v.push_back(MoveOnly{5});
    v.emplace_back(4);
    CHECK(5 == v[0U].get());
    CHECK(4 == v[1U].get());

    vector<MoveOnly> v2 = std::move(v);
    CHECK(5 == v2[0U].get());
    CHECK(4 == v2[1U].get());

    SECTION("Swap")
    {
        vector<MoveOnly> v3;
        v3.swap(v2);

        CHECK(5 == v3[0U].get());
        CHECK(4 == v3[1U].get());
        CHECK(v.empty());
    }
}

