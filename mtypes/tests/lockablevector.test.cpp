#include "catch.hpp"

#include <mtypes/include/vector.hpp>
#include <mtypes/include/types.hpp>
#include <mtypes/include/lockablevector.hpp>

using namespace lib;

TEST_CASE("LocableVector constructors", "[vector]")
{
    /*
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
    */
}
