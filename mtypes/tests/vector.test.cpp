#include "catch.hpp"

#include <mtypes/include/vector.hpp>

using namespace lib;

TEST_CASE("vector constructors", "[vector]")
{
    vector<u32> m;
    CHECK(m.size() == 0);
    CHECK(m.empty());

    m = { 1,9,8,7,6,5,4,3,2,0,1 };
    CHECK(m == vector<u32>{ 1, 9, 8, 7, 6, 5, 4, 3, 2, 0, 1 });

}
