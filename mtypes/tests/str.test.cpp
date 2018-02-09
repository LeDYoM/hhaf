#include "catch.hpp"

#include <mtypes/include/str.hpp>

using namespace lib;

TEST_CASE("str test1", "[str]")
{
    str test1;
    CHECK(test1 == "");
    CHECK(test1.size() == 0);

    test1 = "a";
    CHECK(test1 == "a");
    CHECK(test1.size() == 1);

    char test_str[] = "test1_bigstring_to_test_here_and_now_in_this_test";
    test1 = "test1_bigstring_to_test_here_and_now_in_this_test";
    CHECK(test1 == "test1_bigstring_to_test_here_and_now_in_this_test");
    CHECK(test1.size() == sizeof(test_str)-1);

}
