#include "catch.hpp"

#include <mtypes/include/vector.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>

using namespace lib;

TEST_CASE("LocableVector constructors", "[vector]")
{
    vector<u32> m;
    CHECK(m.size() == 0);
    CHECK(m.empty());

    m = { 1,9,8,7,6,5,4,3,2,0,1 };
    CHECK(m == vector<u32>{ 1, 9, 8, 7, 6, 5, 4, 3, 2, 0, 1 });

	// Copy constructor
	auto m2(m);
	CHECK(m == m2);

	// Move constructor

	auto m3(std::move(m));
	CHECK(m.empty());

	CHECK(m2 == m3);

	// Construct from address and size
	const u32 arr[] = { 4, 3, 2, 1 };
	vector<u32> v(arr, sizeof(arr) / sizeof(u32));
	CHECK(v.size() == 4);
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

TEST_CASE("vector removes", "[vector]")
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
}
