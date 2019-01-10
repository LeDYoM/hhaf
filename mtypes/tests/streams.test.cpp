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

template <typename T>
void check_array(T& a)
{
    for (size_type i = 0U; i < 10U; ++i)
    {
        CHECK(a[i] == i);
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
