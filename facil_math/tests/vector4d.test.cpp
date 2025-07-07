#include "catch_include.hpp"

#include <facil_math/include/vector4d.hpp>
#include <htypes/include/types.hpp>

using namespace htps;
using namespace fmath;

TEST_CASE("vector4d::vector4d", "[vector4d]")
{
    vector4du32 v{};
    CHECK(v.x == 0U);
    CHECK(v.y == 0U);
    CHECK(v.z == 0U);
    CHECK(v.w == 0U);
}

TEST_CASE("vector4d::operator+=", "[vector4d]")
{
    vector4du32 v1{11, 20, 40, 154};
    vector4du32 v2{131, 200, 60, 146};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v1.z == 40U);
    CHECK(v1.w == 154U);

    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);
    CHECK(v2.z == 60U);
    CHECK(v2.w == 146U);

    v1 += v2;

    CHECK(v1.x == 142U);
    CHECK(v1.y == 220U);
    CHECK(v1.z == 100U);
    CHECK(v1.w == 300U);

    vector4df v3{2.5F, 6.3F, 8.9F, 4.5F};
    v3 += v1;
    CHECK(v3.x == 144.5F);
    CHECK(v3.y == 226.3F);
    CHECK(v3.z == 108.9F);
    CHECK(v3.w == 304.5F);
}

TEST_CASE("vector4d::operator-=", "[vector4d]")
{
    vector4ds32 v1{11, 20, 30, 40};
    vector4ds32 v2{131, 200, 350, 500};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v1.z == 30U);
    CHECK(v1.w == 40U);

    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);
    CHECK(v2.z == 350U);
    CHECK(v2.w == 500U);

    v1 -= v2;

    CHECK(v1.x == -120);
    CHECK(v1.y == -180);
    CHECK(v1.z == -320);
    CHECK(v1.w == -460);

    vector4df v3{2.5F, 5.3F, 12.1F, 0.9F};

    v3 -= v1;
    CHECK(v3.x == 122.5F);
    CHECK(v3.y == 185.3F);
    CHECK(v3.z == 332.1F);
    CHECK(v3.w == 460.9F);
}

TEST_CASE("vector4d::operator-", "[vector4d]")
{
    vector4ds32 v1{11, 20, 30, 40};
    vector4ds32 v2{1, 2, 3, 4};

    vector4ds32 v3{v1 - v2};
    CHECK(v3.x == 10);
    CHECK(v3.y == 18);
    CHECK(v3.z == 27);
    CHECK(v3.w == 36);

    vector4ds32 v4{-v1};
    CHECK(v4.x == -11);
    CHECK(v4.y == -20);
    CHECK(v4.z == -30);
    CHECK(v4.w == -40);

    vector4ds32 v5{-v4};
    CHECK(v5.x == 11);
    CHECK(v5.y == 20);
    CHECK(v5.z == 30);
    CHECK(v5.w == 40);

    CHECK(v1.x == 11);
    CHECK(v1.y == 20);
    CHECK(v1.z == 30);
    CHECK(v1.w == 40);

    CHECK(v4.x == -11);
    CHECK(v4.y == -20);
    CHECK(v4.z == -30);
    CHECK(v4.w == -40);
}

TEST_CASE("vector4d::operator*", "[vector4d]")
{
    vector4ds32 v1{11, 20, 40, 50};
    vector4ds32 v2{1, 2, 3, 5};

    vector4ds32 v3{v1 * v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 40);
    CHECK(v3.z == 120);
    CHECK(v3.w == 250);

    v1 *= v2;
    CHECK(v1.x == 11);
    CHECK(v1.y == 40);
    CHECK(v1.z == 120);
    CHECK(v1.w == 250);

    auto v4{3U * v2};
    CHECK(v4.x == 3U);
    CHECK(v4.y == 6U);
    CHECK(v4.z == 9U);
    CHECK(v4.w == 15U);

    auto v5{v2 * 7U};
    CHECK(v5.x == 7U);
    CHECK(v5.y == 14U);
    CHECK(v5.z == 21U);
    CHECK(v5.w == 35U);
}

TEST_CASE("vector4d::operator/", "[vector4d]")
{
    vector4ds32 v1{11, 20, 50, 120};
    vector4ds32 v2{1, 2, 25, 40};

    vector4ds32 v3{v1 / v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 10);
    CHECK(v3.z == 2);
    CHECK(v3.w == 3);

    const s32 scalar{10};
    vector4ds32 v4{v1 / scalar};
    CHECK(v4.x == 1);
    CHECK(v4.y == 2);
    CHECK(v4.z == 5);
    CHECK(v4.w == 12);

    const vector4ds32 v5{20, 50, 100, 200};
    const s32 scalar2{200};
    vector4ds32 v6{scalar2 / v5};
    CHECK(v6.x == 10);
    CHECK(v6.y == 4);
    CHECK(v6.z == 2);
    CHECK(v6.w == 1);
}
