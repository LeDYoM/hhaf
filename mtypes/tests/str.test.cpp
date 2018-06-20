#include "catch.hpp"

#include <mtypes/include/str.hpp>

using namespace lib;

TEST_CASE("constructors", "[str]")
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

TEST_CASE("test2", "[str]")
{
    str test("This");
    test += " is a";
    test += str(" test");
    CHECK(test == "This is a test");
    CHECK(test.size() == sizeof("This is a test")-1);
}

TEST_CASE("test3", "[str]")
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

TEST_CASE("substr", "[str]")
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

TEST_CASE("conversions", "[str]")
{
	str test = 1234567890L;
	CHECK(test == "1234567890");
	test = 'A';
    CHECK(test == "65");
    test = "A";
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

TEST_CASE("str convert", "[str]")
{
	str sInt("-42");
	str sIntCopy(sInt);
	str longStr(12345678900);
	str slongStr(-12345678900);
	s32 i{ 0 };
	f32 j{ 0 };
	u64 k{ 0 };

	CHECK(sInt.convert(i));
	CHECK(i == -42);

    // Int string to f32 works
	CHECK(sInt.convert(j));

	CHECK(sInt == sIntCopy);

	CHECK_FALSE(longStr.convert(i));

    // 64bits signed int to f32 works
	CHECK(longStr.convert(j));
	CHECK(longStr.convert(k));
    CHECK(j == 12345678900.f);
	CHECK(k == 12345678900);

    // Warning: sign mismatch, but works
	CHECK(slongStr.convert(k));
}
