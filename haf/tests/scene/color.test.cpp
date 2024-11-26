#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/color.hpp>
#include <type_traits>

using namespace htps;
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

        CHECK(color.red() == 0U);
        CHECK(color.green() == 0U);
        CHECK(color.blue() == 0U);
        CHECK(color.alpha() == 255U);
    }

    SECTION("Value constructor")
    {
        Color color{1U, 2U, 3U, 4U};

        CHECK(color.red() == 1U);
        CHECK(color.green() == 2U);
        CHECK(color.blue() == 3U);
        CHECK(color.alpha() == 4U);
    }
}

TEST_CASE("Color multiplication", "[color][scene]")
{
    SECTION("operator*=")
    {
        Color color{128U, 128U, 128U};
        color *= 2.0F;

        CHECK(color.red() == 255U);
        CHECK(color.green() == 255U);
        CHECK(color.blue() == 255U);
        CHECK(color.alpha() == 255U);

        color = Color{128U, 128U, 128U};
        color *= 0.0F;

        CHECK(color.red() == 0U);
        CHECK(color.green() == 0U);
        CHECK(color.blue() == 0U);
        CHECK(color.alpha() == 0U);

        color = Color{255U, 255U, 255U};
        color *= 0.5F;

        CHECK(color.red() == 127U);
        CHECK(color.green() == 127U);
        CHECK(color.blue() == 127U);
        CHECK(color.alpha() == 127U);
    }

    SECTION("operator*")
    {
        SECTION("Left side")
        {
            Color color_source{128U, 128U, 128U};
            Color color = color_source * 2.0F;

            CHECK(color.red() == 255U);
            CHECK(color.green() == 255U);
            CHECK(color.blue() == 255U);
            CHECK(color.alpha() == 255U);

            color_source = Color{128U, 128U, 128U};
            color        = color_source * 0.0F;

            CHECK(color.red() == 0U);
            CHECK(color.green() == 0U);
            CHECK(color.blue() == 0U);
            CHECK(color.alpha() == 0U);

            color_source = Color{255U, 255U, 255U};
            color        = color_source * 0.5F;

            CHECK(color.red() == 127U);
            CHECK(color.green() == 127U);
            CHECK(color.blue() == 127U);
            CHECK(color.alpha() == 127U);
        }

        SECTION("Right side")
        {
            Color color_source{128U, 128U, 128U};
            Color color = 2.0F * color_source;

            CHECK(color.red() == 255U);
            CHECK(color.green() == 255U);
            CHECK(color.blue() == 255U);
            CHECK(color.alpha() == 255U);

            color_source = Color{128U, 128U, 128U};
            color        = 0.0F * color_source;

            CHECK(color.red() == 0U);
            CHECK(color.green() == 0U);
            CHECK(color.blue() == 0U);
            CHECK(color.alpha() == 0U);

            color_source = Color{255U, 255U, 255U};
            color        = 0.5F * color_source;

            CHECK(color.red() == 127U);
            CHECK(color.green() == 127U);
            CHECK(color.blue() == 127U);
            CHECK(color.alpha() == 127U);
        }
    }
}

TEST_CASE("Color division", "[color][scene]")
{
    SECTION("operator/=")
    {
        Color color{255U, 255U, 255U, 255U};
        color /= 2.0F;

        CHECK(color.red() == 127U);
        CHECK(color.green() == 127U);
        CHECK(color.blue() == 127U);
        CHECK(color.alpha() == 127U);

        color = Color{128U, 128U, 128U, 128U};
        color /= 0.5F;

        CHECK(color.red() == 255U);
        CHECK(color.green() == 255U);
        CHECK(color.blue() == 255U);
        CHECK(color.alpha() == 255U);
    }

    SECTION("operator/")
    {
        SECTION("Left side")
        {
            Color color_source{128U, 128U, 128U, 128U};
            Color color = color_source / 2.0F;

            CHECK(color.red() == 64U);
            CHECK(color.green() == 64U);
            CHECK(color.blue() == 64U);
            CHECK(color.alpha() == 64U);

            color_source = Color{128U, 128U, 128U, 128U};
            color        = color_source / 1.0F;

            CHECK(color.red() == 128U);
            CHECK(color.green() == 128U);
            CHECK(color.blue() == 128U);
            CHECK(color.alpha() == 128U);

            color_source = Color{255U, 255U, 255U, 255U};
            color        = color_source / 0.5F;

            CHECK(color.red() == 255U);
            CHECK(color.green() == 255U);
            CHECK(color.blue() == 255U);
            CHECK(color.alpha() == 255U);
        }
    }
}

TEST_CASE("Color interpolate", "[color][scene]")
{
    Color start{20U, 20U, 20U, 20U};
    Color end{120U, 120U, 120U, 120U};

    Color color = interpolate(start, end, 0.1F);

    CHECK(color.red() == 30U);
    CHECK(color.green() == 30U);
    CHECK(color.blue() == 30U);
    CHECK(color.alpha() == 30U);

    color = interpolate(start, end, 0.5F);

    CHECK(color.red() == 70U);
    CHECK(color.green() == 70U);
    CHECK(color.blue() == 70U);
    CHECK(color.alpha() == 70U);

    color = interpolate(start, end, 1.0F);

    CHECK(color.red() == 120U);
    CHECK(color.green() == 120U);
    CHECK(color.blue() == 120U);
    CHECK(color.alpha() == 120U);
}
