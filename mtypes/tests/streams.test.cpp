#include "catch.hpp"

#include <mtypes/include/streamin.hpp>
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

	SerializationStreamIn operator>>(SerializationStreamIn& ssi, PODClass& out)
	{
		ssi >> out.a >> out.b >> out.c;
		return ssi;
	}

	bool operator==(const PODClass& lhs, const PODClass& rhs)
	{
		return lhs.a == lhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
	}
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
    SECTION("Appended string")
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

    SECTION("Appended string with divided numbers")
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

    SECTION("Append directly to the input stream")
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

        ssi.setUseNewLineAsSeparator(false) >> a;

        check_array(a);
        CHECK(ssi.eof());
    }

    SECTION("Append directly to the input stream and handle \\n")
    {
        SerializationStreamIn ssi;

		size_type a[10U] = { 0U };

        CHECK(ssi.eof());

		SECTION("With new line as separator")
		{
			ssi << "0,1,2,3,4";
			ssi.append(",5, ");
			ssi << " 6,   7  ,";
			ssi.append("8, 9");
			CHECK_FALSE(ssi.eof());

			ssi.setUseNewLineAsSeparator(false) >> a;

			check_array(a);
			CHECK(ssi.eof());
		}

		SECTION("Without new line as separator")
		{
			ssi << "0,1,2,3,4";
			ssi.append("5");
			ssi << " 6,   7  ";
			ssi.append("8, 9");
			CHECK_FALSE(ssi.eof());

			ssi.setUseNewLineAsSeparator(true) >> a;

			check_array(a);
			CHECK(ssi.eof());
		}
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

TEST_CASE("SerializationStreamIn: getLine", "[streams][SerializationStreamIn]")
{
	{
		SerializationStreamIn ssi(string_vector{ "1,2,", "3,4", "5,6" });
		CHECK_FALSE(ssi.eof());

		str value[2];
		ssi.setUseNewLineAsSeparator(false) >> value;
		CHECK(value[0] == "1");
		CHECK(value[1] == "2");

		ssi.getLine(value[0]);
		CHECK(value[0] == "3,4");

		ssi >> value;
		CHECK(value[0] == "5");
		CHECK(value[1] == "6");
		CHECK(ssi.eof());
	}
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
		CHECK(ssi.eof());
		CHECK_FALSE(ssi.hasError());
	}

    {
        str out;
        ssi += "abc def, ABC  DEF";
        ssi.separator(',') >> out;
        CHECK(ssi.separator() == ',');
        CHECK(out == "abc def");
        ssi >> out;
        CHECK(out == "ABC  DEF");
		CHECK(ssi.eof());
		CHECK_FALSE(ssi.hasError());
    }

    {
        str out;
        ssi += "abc def, ABC  DEF";
        ssi.separator('B') >> out;
        CHECK(out == "abc def, A");
        ssi >> out;
        CHECK(out == "C  DEF");
        CHECK(ssi.separator() == 'B');
		CHECK(ssi.eof());
		CHECK_FALSE(ssi.hasError());
	}

    {
        str out;
        ssi.disableSeparator() << "abc def, ABC  DEF";
        CHECK(ssi.separator() == 0);
        ssi >> out;
        CHECK(out == "abc def, ABC  DEF");
        CHECK(ssi.eof());
		CHECK_FALSE(ssi.hasError());
	}
}

TEST_CASE("SerializationStreamIn: Errors empty data", "[streams][SerializationStreamIn]")
{
	SECTION("Empty data")
	{
		SerializationStreamIn data;
		u32 a;

		data >> a;
		CHECK(data.eof());
		CHECK(data.hasError());
	}

	SECTION("Empty separator data")
	{
		SerializationStreamIn data{ "," };
		u32 a;

		data >> a;
		CHECK(data.eof());
		CHECK(data.hasError());
	}

	SECTION("Empty separator data 2")
	{
		SerializationStreamIn data{ " ," };
		u32 a;

		data >> a;
		CHECK(data.eof());
		CHECK(data.hasError());
	}

	SECTION("Empty separator data 2")
	{
		SerializationStreamIn data{ " , " };
		u32 a;

		data >> a;
		CHECK_FALSE(data.eof());
		CHECK(data.hasError());
	}
}

TEST_CASE("SerializationStreamIn: Errors invalid format", "[streams][SerializationStreamIn]")
{
	SECTION("Try to put str in integer")
	{
		SerializationStreamIn data{ "1abc" };
		u32 a;

		data >> a;
		CHECK(data.eof());
		CHECK_FALSE(data.hasError());
	}
}

TEST_CASE("SerializationStreamIn: Simple serialization", "[streams][SerializationStreamIn]")
{
	SECTION("Completely Correct input")
	{
		SerializationStreamIn data{ "123000,84.234F,500" };
		PODClass a;
		
		data >> a;

		CHECK(a == PODClass{123000, 84.234F, 500});
		CHECK(data.eof());
		CHECK_FALSE(data.hasError());
	}
}
