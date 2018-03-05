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

TEST_CASE("str substr", "[str]")
{
	str test("String to test substr=!other tests");
	CHECK(test.substr(str::npos) == "");
	CHECK(test.substr(str::npos).empty());
	CHECK(test.substr(str::npos).size() == 0);
	CHECK(test.substr(0) == test);
	CHECK(test.substr(7, 21) == "to test substr=!other");
	CHECK(test.substr(7, 21).substr(8,50) == "substr=!other");
	CHECK(test.substr(7, 21).substr(8, 2) == "su");
}

TEST_CASE("str find_first_of", "[str]")
{
	str test("Try to=test! some parsing&&now");

	CHECK(test.find_first_of(' ') == 3);
	CHECK(test.find_first_of('=') == 6);
	CHECK(test.find_first_of('!') == 11);
	CHECK(test.find_first_of('&') == 25);
	test[25] = '/';
	CHECK(test.find_first_of('/') == 25);
	CHECK(test.find_first_of('&') == 26);
}

TEST_CASE("str conversions", "[str]")
{
	str test = 1234567890L;
	CHECK(test == "1234567890");
	test = 'A';
	CHECK(test == "A");
	test.append(9876543210);
	CHECK(test == "A9876543210");
	test += "_";
	test += 1;
	CHECK(test == "A9876543210_1");
	test += 01;
	CHECK(test == "A9876543210_11");
	test += 0xf;
	CHECK(test == "A9876543210_1115");
	test += 010;
	CHECK(test == "A9876543210_11158");
}

TEST_CASE("str operations", "[str]")
{
	str f("the test");
	str f2("hello ");
	CHECK(f2 + f == "hello the test");
	CHECK((f2 += f) == "hello the test");
	CHECK(f2 == "hello the test");
}

TEST_CASE("str split", "[str]")
{
	str foo("hello. This. To Split string. Lets see");
	auto strSplitted = foo.split('.');
	CHECK(strSplitted.size() == 4);
	CHECK(strSplitted[0] == "hello");
	CHECK(strSplitted[1] == " This");
	CHECK(strSplitted[2] == " To Split string");
	CHECK(strSplitted[3] == " Lets see");

	auto moreSplitted(strSplitted[2].substr(4).split('s'));
	CHECK(moreSplitted.size() == 2);
	CHECK(moreSplitted[0] == "Split ");
	CHECK(moreSplitted[1] == "tring");
}
