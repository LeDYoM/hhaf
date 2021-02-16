#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/scene/include/transformation.hpp>

TEST_CASE("haf::scene::Transformation", "[haf][scene][Transformation]")
{
    using namespace haf;
    using namespace haf::scene;

    Transformation transformation;
    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.prop<Position>() = {2.0F, 4.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.prop<Origin>() = {2.0F, 4.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.prop<Scale>() = {2.0F, 4.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.prop<Rotation>() = {2.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.rotateAround({20.0F, 20.0F}, 4.0F);

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.scaleAround({20.0F, 20.0F}, {5.0F, 2.0f});

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());
}
