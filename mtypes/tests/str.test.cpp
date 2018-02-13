#include "catch.hpp"

#include <mtypes/include/str.hpp>

using namespace lib;

TEST_CASE("str test1", "[str]")
{
    str test;
    CHECK(test == "");
    CHECK(test.size() == 0);

    test = "a";
    CHECK(test == "a");
    CHECK(test.size() == 1);

    char test_str[] = "test1_bigstring_to_test_here_and_now_in_this_test";
    test = "test1_bigstring_to_test_here_and_now_in_this_test";
    CHECK(test == "test1_bigstring_to_test_here_and_now_in_this_test");
    CHECK(test.size() == sizeof(test_str)-1);
}

TEST_CASE("str test2", "[str]")
{
    str test("This");
    test += " is a";
    test += str(" test");
    CHECK(test == "This is a test");
    CHECK(test.size() == sizeof("This is a test")-1);
}

TEST_CASE("str test3", "[str]")
{
    str test("Lets play this");
    auto sep{test.find_first_of(' ')};
    CHECK(sep == 4);
    str sub{test.substr(sep+1)};
    CHECK(sub=="play this");
    str sub2{sub.substr(sub.find_first_of('z'))};
    CHECK(sub2=="");
    str sub3{sub.substr(sub.find_first_of(' '))};
    CHECK(sub3==" this");
    sub3 += make_str(3);
    CHECK(sub3 == " this3");
}
