#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/scene/include/color.hpp>
#include <type_traits>

using namespace mtps;
using namespace haf;
using namespace haf::scene;

static_assert(sizeof(Color) == sizeof(u32), "Color size is wrong");
static_assert(std::is_trivially_copy_assignable_v<Color>,
              "Color is not is_trivially_copy_assignable");
static_assert(std::is_trivially_copy_constructible_v<Color>,
              "Color is not is_trivially_copy_constructible");
static_assert(std::is_nothrow_constructible_v<Color>,
              "Color is not is_nothrow_constructible");
static_assert(std::is_nothrow_move_constructible_v<Color>,
              "Color is not is_nothrow_move_constructible");
static_assert(std::is_trivially_destructible_v<Color>,
              "Color is not is_trivially_destructible");
static_assert(std::is_trivially_move_constructible_v<Color>,
              "Color is not is_trivially_move_constructible");
static_assert(std::is_trivially_copyable_v<Color>,
              "Color is not is_trivially_copyable");

TEST_CASE("Color::Color", "[color][scene]")
{
    SECTION("Default constructor")
    {
        Color color;

        CHECK(color.r == 0U);
        CHECK(color.g == 0U);
        CHECK(color.b == 0U);
        CHECK(color.a == 255U);
    }

    SECTION("Value constructor")
    {
        Color color{1U, 2U, 3U, 4U};

        CHECK(color.r == 1U);
        CHECK(color.g == 2U);
        CHECK(color.b == 3U);
        CHECK(color.a == 4U);
    }
}

TEST_CASE("Color multiplication", "[color][scene]")
{
    SECTION("operator*=")
    {
        Color color{128U, 128U, 128U};
        color *= 2.0F;

        CHECK(color.r == 255U);
        CHECK(color.g == 255U);
        CHECK(color.b == 255U);
        CHECK(color.a == 255U);

        color = Color{128U, 128U, 128U};
        color *= 0.0F;

        CHECK(color.r == 0U);
        CHECK(color.g == 0U);
        CHECK(color.b == 0U);
        CHECK(color.a == 0U);

        color = Color{255U, 255U, 255U};
        color *= 0.5F;

        CHECK(color.r == 127U);
        CHECK(color.g == 127U);
        CHECK(color.b == 127U);
        CHECK(color.a == 127U);
    }

    SECTION("operator*")
    {
        Color color_source{128U, 128U, 128U};
        Color color = color_source * 2.0F;

        CHECK(color.r == 255U);
        CHECK(color.g == 255U);
        CHECK(color.b == 255U);
        CHECK(color.a == 255U);

        color_source = Color{128U, 128U, 128U};
        color        = color_source * 0.0F;

        CHECK(color.r == 0U);
        CHECK(color.g == 0U);
        CHECK(color.b == 0U);
        CHECK(color.a == 0U);

        color_source = Color{255U, 255U, 255U};
        color        = color_source * 0.5F;

        CHECK(color.r == 127U);
        CHECK(color.g == 127U);
        CHECK(color.b == 127U);
        CHECK(color.a == 127U);
    }
}
