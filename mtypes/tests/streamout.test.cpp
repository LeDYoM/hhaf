#include "catch.hpp"

#include <mtypes/include/streamout.hpp>
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

    SerializationStreamOut operator<<(SerializationStreamOut& sso, const PODClass& in)
    {
        sso << in.a << in.b << in.c;
        return sso;
    }

    bool operator==(const PODClass& lhs, const PODClass& rhs)
    {
        return lhs.a == lhs.a && lhs.b == rhs.b && lhs.c == rhs.c;
    }
}

TEST_CASE("SerializationStreamOut", "[streams][SerializationStreamIn]")
{
    SECTION("Simple")
    {
        str data{ "1, 2" };
        SerializationStreamOut sso;

        int a{ 0U };
        int b{ 0U };

        sso << a;
        sso << b;

        CHECK(sso.data() == "0,0");
    }

    SECTION("Simple 2")
    {
        SerializationStreamOut sso;

        size_type a[10U] = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U };

        SECTION("Normal")
        {
            sso << a[0] << a[1] << a[2] << a[3] << a[4] << a[5] << a[6] << a[7] << a[8] << a[9];

            CHECK(sso.data() == "0,1,2,3,4,5,6,7,8,9");
        }

        SECTION("Built-in array")
        {
            sso << a;

            CHECK(sso.data() == "0,1,2,3,4,5,6,7,8,9");
        }
    }

        SECTION("Simple change separator")
    {
        str data{ "1, 2" };
        SerializationStreamOut sso;
        CHECK(sso.separator(";/") == ",");

        int a{ 0U };
        int b{ 0U };

        sso << a;
        sso << b;

        CHECK(sso.data() == "0;/0");
    }

    SECTION("Simple 2 change separator")
    {
        SerializationStreamOut sso;
        CHECK(sso.separator(";/") == ",");

        size_type a[10U] = { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U };

        SECTION("Normal")
        {
            sso << a[0] << a[1] << a[2] << a[3] << a[4] << a[5] << a[6] << a[7] << a[8] << a[9];

            CHECK(sso.data() == "0;/1;/2;/3;/4;/5;/6;/7;/8;/9");
        }

        SECTION("Built-in array")
        {
            sso << a;

            CHECK(sso.data() == "0;/1;/2;/3;/4;/5;/6;/7;/8;/9");
        }
    }

}
