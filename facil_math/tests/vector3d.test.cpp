#include "catch_include.hpp"

#include <facil_math/include/vector3d.hpp>
#include <htypes/include/types.hpp>

using namespace htps;
using namespace fmath;

TEST_CASE("vector3d::vector3d", "[vector3d]")
{
    vector3du32 v{};
    CHECK(v.x == 0U);
    CHECK(v.y == 0U);
    CHECK(v.z == 0U);
}

TEST_CASE("vector3d::operator+=", "[vector3d]")
{
    vector3du32 v1{11, 20, 40};
    vector3du32 v2{131, 200, 60};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v1.z == 40U);
    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);
    CHECK(v2.z == 60U);

    v1 += v2;

    CHECK(v1.x == 142U);
    CHECK(v1.y == 220U);
    CHECK(v1.z == 100U);

    vector3df v3{2.5F, 6.3F, 8.9F};
    v3 += v1;
    CHECK(v3.x == 144.5F);
    CHECK(v3.y == 226.3F);
    CHECK(v3.z == 108.9F);
}

TEST_CASE("vector3d::operator-=", "[vector3d]")
{
    vector3ds32 v1{11, 20, 30};
    vector3ds32 v2{131, 200, 350};

    CHECK(v1.x == 11U);
    CHECK(v1.y == 20U);
    CHECK(v1.z == 30U);
    CHECK(v2.x == 131U);
    CHECK(v2.y == 200U);
    CHECK(v2.z == 350U);

    v1 -= v2;

    CHECK(v1.x == -120);
    CHECK(v1.y == -180);
    CHECK(v1.z == -320);

    vector3df v3{2.5F, 5.3F, 12.1F};

    v3 -= v1;
    CHECK(v3.x == 122.5F);
    CHECK(v3.y == 185.3F);
    CHECK(v3.z == 332.1F);
}

TEST_CASE("vector3d::operator-", "[vector3d]")
{
    vector3ds32 v1{11, 20, 30};
    vector3ds32 v2{1, 2, 3};

    vector3ds32 v3{v1 - v2};
    CHECK(v3.x == 10);
    CHECK(v3.y == 18);
    CHECK(v3.z == 27);

    vector3ds32 v4{-v1};
    CHECK(v4.x == -11);
    CHECK(v4.y == -20);
    CHECK(v4.z == -30);

    vector3ds32 v5{-v4};
    CHECK(v5.x == 11);
    CHECK(v5.y == 20);
    CHECK(v5.z == 30);

    CHECK(v1.x == 11);
    CHECK(v1.y == 20);
    CHECK(v1.z == 30);

    CHECK(v4.x == -11);
    CHECK(v4.y == -20);
    CHECK(v4.z == -30);
}

TEST_CASE("vector3d::operator*", "[vector3d]")
{
    vector3ds32 v1{11, 20, 40};
    vector3ds32 v2{1, 2, 3};

    vector3ds32 v3{v1 * v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 40);
    CHECK(v3.z == 120);

    v1 *= v2;
    CHECK(v1.x == 11);
    CHECK(v1.y == 40);
    CHECK(v1.z == 120);
}

TEST_CASE("vector3d::operator/", "[vector3d]")
{
    vector3ds32 v1{11, 20, 50};
    vector3ds32 v2{1, 2, 25};

    vector3ds32 v3{v1 / v2};
    CHECK(v3.x == 11);
    CHECK(v3.y == 10);
    CHECK(v3.z == 2);

    const s32 scalar{10};
    vector3ds32 v4{v1 / scalar};
    CHECK(v4.x == 1);
    CHECK(v4.y == 2);
    CHECK(v4.z == 5);

    const vector3ds32 v5{20, 50, 100};
    const s32 scalar2{200};
    vector3ds32 v6{scalar2 / v5};
    CHECK(v6.x == 10);
    CHECK(v6.y == 4);
    CHECK(v6.z == 2);
}
