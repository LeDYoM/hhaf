#include "catch.hpp"

#include <haf/include/resources/image.hpp>

using namespace haf;
using namespace haf::core;
using namespace haf::res;
using namespace fmath;

TEST_CASE("haf::resources::Image", "[haf][resources][Image]")
{
    {
        Image a;
        CHECK(a.size() == vector2du32{0U, 0U});
        CHECK(a.channels() == 0U);
        CHECK(a.containsImage() == false);
        CHECK(a.isValid() == false);
    }

    {
        Image a{{16, 16}, 1U};
        CHECK(a.size() == vector2du32{16U, 16U});
        CHECK(a.channels() == 1U);
        CHECK(a.containsImage());
        CHECK(a.isValid());
    }
}

TEST_CASE("haf::resources::Image::fill_pixel_size_1", "[haf][resources][Image]")
{
    Image a{{16U, 16U}, 1U};
    CHECK(a.size() == vector2du32{16U, 16U});
    CHECK(a.channels() == 1U);
    CHECK(a.containsImage());
    CHECK(a.isValid());

    CHECK_FALSE(a.fill({17, 0U}, {15U, 15U}, {0U, 0U, 0U, 0U}));
    CHECK_FALSE(a.fill({0, 0U}, {0U, 17U}, {0U, 0U, 0U, 0U}));

    a.fill({5U, 5U, 5U, 5U});

    {
        auto const pixel{a.getPixel({1U, 1U})};
        CHECK(pixel.x == 5U);
    }

    CHECK(a.fill({5, 5U}, {15U, 15U}, {1U, 2U, 3U, 4U}));

    {
        auto const pixel{a.getPixel({1U, 1U})};
        CHECK(pixel.x == 5U);
    }

    {
        auto const pixel{a.getPixel({5U, 5U})};
        CHECK(pixel.x == 1U);
    }

    {
        auto const pixel{a.getPixel({15U, 15U})};
        CHECK(pixel.x == 1U);
    }
}

TEST_CASE("haf::resources::Image::fill_pixel_size_4", "[haf][resources][Image]")
{
    Image a{{128U, 16U}, 4U};
    CHECK(a.size() == vector2du32{128U, 16U});
    CHECK(a.channels() == 4U);
    CHECK(a.containsImage());
    CHECK(a.isValid());

    CHECK_FALSE(a.fill({0U, 17U}, {15U, 15U}, {0U, 0U, 0U, 0U}));
    CHECK_FALSE(a.fill({0U, 0U}, {0U, 17U}, {0U, 0U, 0U, 0U}));

    a.fill({5U, 6U, 7U, 8U});

    {
        auto const pixel{a.getPixel({1U, 1U})};
        CHECK(pixel.x == 5U);
        CHECK(pixel.y == 6U);
        CHECK(pixel.z == 7U);
        CHECK(pixel.w == 8U);
    }

    CHECK(a.fill({5, 5U}, {15U, 15U}, {1U, 2U, 3U, 4U}));

    {
        auto const pixel{a.getPixel({1U, 1U})};
        CHECK(pixel.x == 5U);
        CHECK(pixel.y == 6U);
        CHECK(pixel.z == 7U);
        CHECK(pixel.w == 8U);
    }

    {
        auto const pixel{a.getPixel({5U, 5U})};
        CHECK(pixel.x == 1U);
        CHECK(pixel.y == 2U);
        CHECK(pixel.z == 3U);
        CHECK(pixel.w == 4U);
    }

    {
        auto const pixel{a.getPixel({15U, 15U})};
        CHECK(pixel.x == 1U);
        CHECK(pixel.y == 2U);
        CHECK(pixel.z == 3U);
        CHECK(pixel.w == 4U);
    }
}

TEST_CASE("haf::resources::Image::get_set_pixel_pixel_size_1",
          "[haf][resources][Image]")
{
    {
        Image a;
        CHECK_FALSE(a.setPixel({0U, 0U}, {0U, 0U, 0U, 0U}));
    }

    Image a{{128U, 128U}, 1U};
    a.fill({5U, 5U, 5U, 5U});

    CHECK_FALSE(a.setPixel({128U, 128U}, {0U, 0U, 0U, 0U}));

    CHECK(a.setPixel({0, 0U}, {2U, 2U, 2U, 2U}));

    {
        auto const pixel{a.getPixel({0U, 0U})};
        CHECK(pixel.x == 2U);
    }

    {
        auto const pixel{a.getPixel({1U, 1U})};
        CHECK(pixel.x == 5U);
    }

    {
        auto const pixel{a.getPixel({128U, 128U})};
        CHECK(pixel.x == 0U);
    }
}
