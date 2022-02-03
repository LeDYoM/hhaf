#include "catch.hpp"

#include <htypes/include/str.hpp>
#include <cstring>

using namespace htps;

TEST_CASE("str::str Default constructor", "[str]")
{
    str test;
    CHECK(test == "");
    CHECK(test.size() == 0);
    CHECK(test.empty());
    CHECK_FALSE(test == "abc");

    test.push_back('S');
    CHECK(test == "S");
    CHECK(test == str{"S"});
    CHECK(test.size() == 1U);
}

TEST_CASE("str::str Copy initialize", "[str]")
{
    str test("a");
    CHECK(test == "a");
    CHECK(test.size() == 1);

    str test2 = "a";
    CHECK(test2 == "a");
    CHECK(test2.size() == 1);

    char test_str[] = "test1_bigstring_to_test_here_and_now_in_this_test";
    str test3       = "test1_bigstring_to_test_here_and_now_in_this_test";
    CHECK(test3 == "test1_bigstring_to_test_here_and_now_in_this_test");
    CHECK(test3.size() == sizeof(test_str) - 1);
}

TEST_CASE("str::str Copy", "[str]")
{
    str test;
    test = "def";
    CHECK(test == "def");
    CHECK_FALSE(test != "def");
    CHECK_FALSE(test == "de");
    CHECK_FALSE(test == "def0");
    CHECK(test == "def");
    CHECK_FALSE(test == "");
    CHECK_FALSE("def" != test);
    CHECK_FALSE("de" == test);
    CHECK_FALSE("def0" == test);
    CHECK("def" == test);
    CHECK_FALSE("" == test);
}

TEST_CASE("str::operator= copy","[str]")
{
    str test = "Long enought string";
    str test2 = "abc";
    auto const capacity_now_test{test.capacity()};

    test = test2;
    CHECK(test.capacity() >= capacity_now_test);
}

TEST_CASE("str::Increment", "[str]")
{
    str test("This");
    test += " is a";
    test += str(" test");
    CHECK(test == "This is a test");
    CHECK(test.size() == sizeof("This is a test") - 1);
}

TEST_CASE("str::find", "[str]")
{
    str test("Lets play this");
    auto sep{test.find(' ')};
    CHECK(sep == 4U);
    str sub{test.substr(sep + 1)};
    CHECK(sub == "play this");
    str sub2{sub.substr(sub.find('z'))};
    CHECK(sub2 == "");
    str sub3{sub.substr(sub.find(' '))};
    CHECK(sub3 == " this");
    sub3 += make_str(3U);
    CHECK(sub3 == " this3");
}

TEST_CASE("str::substr", "[str]")
{
    str test("String to test substr=!other tests");
    CHECK(test.substr(str::npos) == "");
    CHECK(test.substr(str::npos).empty());
    CHECK(test.substr(str::npos).size() == 0U);
    CHECK(test.substr(0) == test);
    CHECK(test.substr(7, 21) == "to test substr=!other");
    CHECK(test.substr(7, 21).substr(8, 50) == "substr=!other");
    CHECK(test.substr(7, 21).substr(8, 2) == "su");
}

TEST_CASE("str::find_first_of", "[str]")
{
    str test("Try to=test! some parsing&&now");

    CHECK(test.find(' ') == 3);
    CHECK(test.find('=') == 6);
    CHECK(test.find('!') == 11);
    CHECK(test.find('&') == 25);
    test[25] = '/';
    CHECK(test.find('/') == 25);
    CHECK(test.find('&') == 26);
}

TEST_CASE("str conversions", "[str]")
{
    str test = str::to_str(static_cast<u64>(1234567890L));
    CHECK(test == "1234567890");
    test = str::to_str('A');
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

TEST_CASE("str::split", "[str]")
{
    str foo("hello. This. To Split string. Lets see.");
    auto strSplitted = foo.split('.');
    CHECK(strSplitted.size() == 5);
    CHECK(strSplitted[0U] == "hello");
    CHECK(strSplitted[1U] == " This");
    CHECK(strSplitted[2U] == " To Split string");
    CHECK(strSplitted[3U] == " Lets see");
    CHECK(strSplitted[4U] == "");

    auto moreSplitted(strSplitted[2].substr(4).split('s'));
    CHECK(moreSplitted.size() == 2);
    CHECK(moreSplitted[0U] == "Split ");
    CHECK(moreSplitted[1U] == "tring");
}

TEST_CASE("str trims", "[str]")
{
    SECTION("ltrim")
    {
        str tst_str(" \f\n\r\t\va");
        tst_str.ltrim();
        CHECK(tst_str == "a");
    }

    SECTION("rtrim")
    {
        str tst_str("a \f\n\r\t\v");
        tst_str.rtrim();
        CHECK(tst_str == "a");
    }

    SECTION("trim")
    {
        str tst_str(" \f\n\r\t\va \f\n\r\t\v");
        tst_str.trim();
        CHECK(tst_str == "a");
    }

    SECTION("trim misc")
    {
        str tst_str(" \f\n\r\t\va b \f\n\r\t\v");
        tst_str.trim();
        CHECK(tst_str == "a b");

        tst_str = " \f\n\r\t\va b \f\n\r\t\v";
        tst_str.ltrim();
        CHECK(tst_str == "a b \f\n\r\t\v");

        tst_str = " \f\n\r\t\va b \f\n\r\t\v";
        tst_str.rtrim();
        CHECK(tst_str == " \f\n\r\t\va b");

        tst_str = " \f\n\r\t\va b \f\n\r\t\v";
        tst_str.ltrim();
        CHECK(tst_str == "a b \f\n\r\t\v");
        tst_str.rtrim();
        CHECK(tst_str == "a b");

        SECTION("trim misc 2")
        {
            tst_str += "qwe   ";
            tst_str = "    def" + tst_str;
            tst_str.trim();
            CHECK(tst_str == "defa bqwe");
        }
    }
}

TEST_CASE("str::convert", "[str]")
{
    str sInt("-42");
    str sIntCopy(sInt);
    str longStr(str::to_str(12345678900));
    str slongStr(str::to_str(-12345678900));
    s32 i{0};
    f32 j{0};
    u64 k{0};

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

TEST_CASE("str::has", "[str]")
{
    str tst_string{"String to test the has in function"};

    CHECK(tst_string.has("to test") == 7U);
    CHECK(tst_string.has("totest") == str::npos);
    CHECK(tst_string.has("String to test the has in function") == 0U);
    CHECK(tst_string.has("tring to test the has in function") == 1U);
    CHECK(tst_string.has("String to test the has in function ") == str::npos);
    CHECK(tst_string.has("function") == 26U);
    CHECK_FALSE(tst_string.has("function ") == str::npos);
    CHECK_FALSE(tst_string.has("") == 0U);
}

TEST_CASE("str::has_in", "[str]")
{
    str tst_string{"String to test the has in function"};

    CHECK(tst_string.has_in("to test", 7U));
    CHECK(tst_string.has_in("function", 26U));
    CHECK_FALSE(tst_string.has_in("function ", 26U));
    CHECK_FALSE(tst_string.has_in("function", 56U));
    CHECK_FALSE(tst_string.has_in("", 156U));
    CHECK(tst_string.has_in("", 15U));
}

TEST_CASE("str starts and ends with", "[str]")
{
    str tst_string("String to test");

    SECTION("Starts with")
    {
        CHECK(tst_string.starts_with(""));
        CHECK(tst_string.starts_with("String "));
        CHECK(tst_string.starts_with("String to test"));
        CHECK_FALSE(tst_string.starts_with(" "));
        CHECK_FALSE(tst_string.starts_with("Stringt"));
        CHECK_FALSE(tst_string.starts_with("String to test "));
        CHECK(tst_string.starts_with(""));
    }

    SECTION("Ends with")
    {
        CHECK(tst_string.ends_with(""));
        CHECK(tst_string.ends_with(" test"));
        CHECK(tst_string.ends_with("String to test"));
        CHECK_FALSE(tst_string.ends_with(" "));
        CHECK_FALSE(tst_string.ends_with("ttest"));
        CHECK_FALSE(tst_string.ends_with("String to test "));
        CHECK(tst_string.ends_with(""));
    }
}

TEST_CASE("str::c_str", "[str]")
{
    {
        str test{"str_test_data"};
        CHECK(0 == std::strcmp("str_test_data", test.c_str()));
        test += "_good";
        CHECK(0 == std::strcmp("str_test_data_good", test.c_str()));

        test = test.substr(1U);
        CHECK(0 != std::strcmp("str_test_data_good", test.c_str()));
        CHECK(0 == std::strcmp("tr_test_data_good", test.c_str()));
    }

    {
        str test;
        CHECK(0 == std::strcmp("", test.c_str()));
        test.push_back('b');
        CHECK_FALSE(test.empty());
        CHECK(0 == std::strcmp("b", test.c_str()));

        test = test.substr(1U);
        CHECK(test.empty());
        CHECK(0 == std::strcmp("", test.c_str()));

        test = test.substr(1U);
        CHECK(test.empty());
        CHECK(0 == std::strcmp("", test.c_str()));
    }
}
