#include "catch.hpp"

#undef TESTABLE_PRIVATE
#define TESTABLE_PRIVATE    public

#include <mtypes/include/types.hpp>
#include <haf/scene/include/transformable.hpp>
#include "matrix_utils.hpp"

using namespace haf;
using namespace haf::scene;
using namespace haf::scene::testing;

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

    SECTION("UpdateTransformIfNecessary")
    {
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
        CHECK(transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK_FALSE(transformable.updateTransformIfNecessary());
    }

    SECTION("UpdateLocalTransformIfNecessary")
    {
        CHECK(transformable.numTransformations() == 1U);
        CHECK(transformable.addTransformation() == 2U);

        CHECK(transformable.updateLocalTransformationsIfNecessary());

        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());

        transformable.prop<Origin>() = {2.0F, 4.0F};
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK(transformable.updateLocalTransformationsIfNecessary());

        transformable.getTransformation(1U).prop<Origin>() = {2.0F, 4.0F};
        CHECK(transformable.updateLocalTransformationsIfNecessary());
        CHECK_FALSE(transformable.updateTransformIfNecessary());
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());
    }
}

TEST_CASE("haf::scene::Transformable check math",
          "[haf][scene][Transformable]")
{
    Transformable transformable;
    transformable.prop<Position>() = {3.0F, 3.0F};

    Transformable transformable_temp;
    transformable_temp.prop<Position>() = {2.0F, 2.0F};

    CHECK(transformable_temp.updateLocalTransformationsIfNecessary());
    CHECK(transformable.updateLocalTransformationsIfNecessary());
    CHECK_FALSE(isAlmostEqual(transformable_temp.localTransform(), transformable.localTransform()));

    transformable.prop<Position>() = {2.0F, 2.0F};
    CHECK(transformable.updateLocalTransformationsIfNecessary());
    CHECK(isAlmostEqual(transformable_temp.localTransform(), transformable.localTransform()));
}