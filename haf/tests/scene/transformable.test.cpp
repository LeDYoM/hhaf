#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <haf/scene/include/transformable.hpp>

TEST_CASE("haf::scene::Transformable", "[haf][scene][Transformable]")
{
    using namespace haf;
    using namespace haf::scene;

    Transformable transformable;
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.prop<Position>() = {2.0F, 4.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.prop<Origin>() = {2.0F, 4.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.prop<Scale>() = {2.0F, 4.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.prop<Rotation>() = {2.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.rotateAround({20.0F, 20.0F}, 4.0F);

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.scaleAround({20.0F, 20.0F}, {5.0F, 2.0f});

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());
}
