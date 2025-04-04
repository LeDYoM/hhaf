#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <facil_math/include/rect.hpp>

using namespace htps;
using namespace fmath;

TEST_CASE("Rect::Rect", "[Rect]")
{
    Rect<f32> rect{2.0F, 3.0F, 4.0F, 5.0F};
    CHECK(rect.size() == vector2d<f32>{4.0F, 5.0F});
}

TEST_CASE("rectFromCenterAndRadius", "[Rect]")
{
    Rect<s32> rect{rectFromCenterAndRadius<s32>(vector2d<s32>{40, 60},
                                                vector2d<s32>{15, 25})};
    CHECK(rect.size() == vector2d<s32>{30, 50});
    CHECK(rect.left == 25);
    CHECK(rect.width == 30);
    CHECK(rect.top == 35);
    CHECK(rect.height == 50);

    CHECK(rect.leftTop() == vector2d<s32>{25, 35});
    CHECK(rect.rightBottom() == vector2d<s32>{55, 85});
    CHECK(rect.center() == vector2d<s32>{40, 60});
    CHECK(rect.radius() == vector2d<s32>{15, 25});
}

TEST_CASE("rectFromCenterAndSize", "[Rect]")
{
    Rect<s32> rect{rectFromCenterAndSize<s32>(vector2d<s32>{50, 80},
                                              vector2d<s32>{20, 30})};
    CHECK(rect.size() == vector2d<s32>{20, 30});
    CHECK(rect.left == 40);
    CHECK(rect.width == 20);
    CHECK(rect.top == 65);
    CHECK(rect.height == 30);

    CHECK(rect.leftTop() == vector2d<s32>{40, 65});
    CHECK(rect.rightBottom() == vector2d<s32>{60, 95});
    CHECK(rect.center() == vector2d<s32>{50, 80});
    CHECK(rect.radius() == vector2d<s32>{10, 15});
}
