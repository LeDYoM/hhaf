#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <haf/scene/include/transformable.hpp>

using namespace haf;
using namespace haf::scene;

TEST_CASE("haf::scene::Transformable", "[haf][scene][Transformable]")
{
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

TEST_CASE("haf::scene::Transformable adding transformations",
          "[haf][scene][Transformable]")
{
    Transformable transformable;
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    CHECK(transformable.numTransformations() == 1U);
    CHECK(transformable.addTransformation() == 2U);

    CHECK_FALSE(
        transformable.getTransformation(0U).updateTransformIfNecessary());

    CHECK(transformable.getTransformation(1U).updateTransformIfNecessary());
    CHECK_FALSE(
        transformable.getTransformation(1U).updateTransformIfNecessary());

    transformable.prop<Origin>() = {2.0F, 4.0F};
    CHECK_FALSE(
        transformable.getTransformation(1U).updateTransformIfNecessary());    
    CHECK(transformable.updateTransformIfNecessary());

    transformable.getTransformation(1U).prop<Origin>() = {2.0F, 4.0F};
    CHECK(
        transformable.getTransformation(1U).updateTransformIfNecessary());    
    CHECK_FALSE(transformable.updateTransformIfNecessary());
}
