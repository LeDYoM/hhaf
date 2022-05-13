#include "catch.hpp"

#include <htypes/include/vector2d.hpp>
#include <htypes/include/types.hpp>

using namespace htps;

TEST_CASE("vector2d::vector2d", "[vector2d]")
{
    vector2du32 v{};
    CHECK(v.x == 0U);
    CHECK(v.y == 0U);
}

TEST_CASE("vector2d::operator+=", "[vector2d]")
{
    vector2du32 v1{11, 20};
    vector2du32 v2{131, 200};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);

    v1 += v2;

    CHECK(v1.x == 142U);
    CHECK(v1.y == 220U);

    vector2df v3{2.5F, 6.3F};
    v3 += v1;
    CHECK(v3.x == 144.5F);
    CHECK(v3.y == 226.3F);
}

TEST_CASE("vector2d::operator-=", "[vector2d]")
{
    vector2ds32 v1{11, 20};
    vector2ds32 v2{131, 200};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);

    v1 -= v2;

    CHECK(v1.x == -120);
    CHECK(v1.y == -180);

    vector2df v3{2.5F, 5.3F};
    v3 -= v1;
    CHECK(v3.x == 122.5F);
    CHECK(v3.y == 185.3F);
}

TEST_CASE("vector2d::operator-", "[vector2d]")
{
    vector2ds32 v1{11, 20};
    vector2ds32 v2{1, 2};

    vector2ds32 v3{v1 - v2};
    CHECK(v3.x == 10);
    CHECK(v3.y == 18);

    vector2ds32 v4{-v1};
    CHECK(v4.x == -11);
    CHECK(v4.y == -20);
}

TEST_CASE("vector2d::operator*", "[vector2d]")
{
    vector2ds32 v1{11, 20};
    vector2ds32 v2{1, 2};

    vector2ds32 v3{v1 * v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 40);
}

TEST_CASE("vector2d::operator/", "[vector2d]")
{
    vector2ds32 v1{11, 20};
    vector2ds32 v2{1, 2};

    vector2ds32 v3{v1 / v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 10);
}
