#include "catch.hpp"

#include <mtypes/include/streams.hpp>
#include <mtypes/include/types.hpp>

using namespace lib;

namespace
{
    struct PODClass
    {
        int a;
        float b;
        short c;
    };
}

template <typename T, size_type Size>
void check_array(T(&data)[Size])
{
    for (size_type i = 0U; i < Size; ++i)
    {
        CHECK(data[i] == i);
    }
}

TEST_CASE("SerializationStreamIn", "[streams][SerializationStreamIn]")
{
    SECTION("Simple")
    {
        str data{ "1, 2" };
        SerializationStreamIn ssi{ std::move(data) };

        int a{ 0U };
        int b{ 0U };

        ssi >> a;
        ssi >> b;

        CHECK(a == 1U);
        CHECK(b == 2U);
    }

    SECTION("Simple 2")
    {
        str data{ "  0,  1  ,  2,3, 4, 5  ,6,\t7,8,   9   " };
        SerializationStreamIn ssi{ std::move(data) };

        size_type a[10U] = { 0U };

        SECTION("Normal")
        {
            ssi >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6] >> a[7] >> a[8] >> a[9];

            check_array(a);
            CHECK(ssi.eof());
        }

        SECTION("Built-in array")
        {
            ssi >> a;

            check_array(a);
            CHECK(ssi.eof());
        }
    }
}

TEST_CASE("SerializationStreamIn::append", "[streams][SerializationStreamIn]")
{
    SECTION("Test1: Appended string")
    {
        str data("0,1,2,3");
        size_type a[10U] = { 0U };

        data << ",4,5,";
        data.append("  6,7 ,");
        data << "8";
        data.append(",9 ");

        SerializationStreamIn ssi{ std::move(data) };
        ssi >> a;

        check_array(a);
        CHECK(ssi.eof());
    }

    SECTION("Test2: Appended string with divided numbers")
    {
        str data("0,1,2,3,4,5,6,7,8,9");
        size_type a[11U] = { 0U };

        data << ",1";
        data << "0";

        SerializationStreamIn ssi{ std::move(data) };

        ssi >> a;

        check_array(a);
        CHECK(ssi.eof());
    }

    SECTION("Test3: Append directly to the input stream")
    {
        SerializationStreamIn ssi;
        size_type a[10U] = { 0U };

        CHECK(ssi.eof());

        ssi << "0,1,2,3";
        ssi << ",4,5,";
        ssi.append("  6,7 ,");
        ssi << "8";
        ssi.append(",9 ");
        CHECK_FALSE(ssi.eof());

        ssi >> a;

        check_array(a);
        CHECK(ssi.eof());
    }

    SECTION("Test3: Append directly to the input stream and handle \\n")
    {
        SerializationStreamIn ssi;
        size_type a[10U] = { 0U };

        CHECK(ssi.eof());

        ssi << "0,1,2,3,4";
        ssi.append(",5, ");
        ssi << " 6,   7  ,";
        ssi.append("8, 9");
        CHECK_FALSE(ssi.eof());

        ssi >> a;

        check_array(a);
        CHECK(ssi.eof());
    }
}

TEST_CASE("SerializationStreamIn: Output to string", "[streams][SerializationStreamIn]")
{
    SerializationStreamIn ssi("abc def, ABC  DEF");
    CHECK_FALSE(ssi.eof());

    str out;
    ssi >> out;
    CHECK(out == "abc def");
    ssi >> out;
    CHECK(out == "ABC  DEF");
}

TEST_CASE("SerializationStreamIn: Separtors", "[streams][SerializationStreamIn]")
{
    SerializationStreamIn ssi("abc def, ABC  DEF");
    CHECK_FALSE(ssi.eof());

    {
        str out;
        ssi >> out;
        CHECK(out == "abc def");
        ssi >> out;
        CHECK(out == "ABC  DEF");
    }

    {
        str out;
        ssi += "abc def, ABC  DEF";
        ssi.separator(',') >> out;
        CHECK(ssi.separator() == ',');
        CHECK(out == "abc def");
        ssi >> out;
        CHECK(out == "ABC  DEF");
    }

    {
        str out;
        ssi += "abc def, ABC  DEF";
        ssi.separator('B') >> out;
        CHECK(out == "abc def, A");
        ssi >> out;
        CHECK(out == "C  DEF");
        CHECK(ssi.separator() == 'B');
    }

    {
        str out;
        ssi.disableSeparator() << "abc def, ABC  DEF";
        CHECK(ssi.separator() == 0);
        ssi >> out;
        CHECK(out == "abc def, ABC  DEF");
        CHECK(ssi.eof());
    }
}
