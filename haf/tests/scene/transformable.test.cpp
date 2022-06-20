#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include "matrix_utils.hpp"

using namespace haf;
using namespace haf::scene;
using namespace haf::scene::testing;

TEST_CASE("haf::scene::Transformable", "[haf][scene][Transformable]")
{
    TransformableSceneNode transformable{nullptr, ""};
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.Position = {2.0F, 4.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.Scale = {2.0F, 4.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    transformable.Rotation = {2.0F};

    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());
}

TEST_CASE("haf::scene::Transformable adding transformations",
          "[haf][scene][Transformable]")
{
    TransformableSceneNode transformable{nullptr, ""};
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    SECTION("UpdateTransformIfNecessary")
    {
        CHECK(transformable.numTransformations() == 1U);
        CHECK(transformable.addTransformation() == 1U);

        CHECK_FALSE(
            transformable.getTransformation(0U).updateTransformIfNecessary());

        CHECK(transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());

        transformable.Position = {2.0F, 4.0F};
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK(transformable.updateTransformIfNecessary());

        transformable.getTransformation(1U).Position = {2.0F, 4.0F};
        CHECK(transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK_FALSE(transformable.updateTransformIfNecessary());
    }

    SECTION("UpdateLocalTransformIfNecessary")
    {
        CHECK(transformable.numTransformations() == 1U);
        CHECK(transformable.addTransformation() == 1U);

        CHECK(transformable.updateLocalTransformationsIfNecessary());

        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());

        transformable.Position = {2.0F, 4.0F};
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());
        CHECK(transformable.updateLocalTransformationsIfNecessary());

        transformable.getTransformation(1U).Position = {2.0F, 4.0F};
        CHECK(transformable.updateLocalTransformationsIfNecessary());
        CHECK_FALSE(transformable.updateTransformIfNecessary());
        CHECK_FALSE(
            transformable.getTransformation(1U).updateTransformIfNecessary());
    }
}

TEST_CASE("haf::scene::Transformable remove transformations")
{
    TransformableSceneNode transformable{nullptr, ""};
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(transformable.updateTransformIfNecessary());

    auto const tr2 = transformable.addTransformation();
    CHECK(transformable.numTransformations() == 2U);

    SECTION("Local check for second")
    {
        CHECK(
            transformable.getTransformation(tr2).updateTransformIfNecessary());
        CHECK_FALSE(
            transformable.getTransformation(tr2).updateTransformIfNecessary());
    }

    SECTION("Local transformation")
    {
        CHECK(transformable.updateLocalTransformationsIfNecessary());
        CHECK_FALSE(transformable.updateLocalTransformationsIfNecessary());
    }

    SECTION("Global transformation")
    {
        Matrix4x4 matrix{Matrix4x4::Identity};
        {
            SceneRenderContext sceneRenderContext{false, matrix};
            transformable.postUpdate(sceneRenderContext);
            CHECK(sceneRenderContext.parentTransformationChanged_);
        }
        {
            SceneRenderContext sceneRenderContext{false, matrix};
            transformable.postUpdate(sceneRenderContext);
            CHECK_FALSE(sceneRenderContext.parentTransformationChanged_);
        }
    }
}

TEST_CASE("haf::scene::Transformable check math", "[haf][scene][Transformable]")
{
    TransformableSceneNode transformable{nullptr, ""};
    transformable.Position = {3.0F, 3.0F};

    TransformableSceneNode transformable_temp{nullptr, ""};
    transformable_temp.Position = {2.0F, 2.0F};

    CHECK(transformable_temp.updateLocalTransformationsIfNecessary());
    CHECK(transformable.updateLocalTransformationsIfNecessary());
    CHECK_FALSE(isAlmostEqual(transformable_temp.localTransform(),
                              transformable.localTransform()));

    transformable.Position = {2.0F, 2.0F};
    CHECK(transformable.updateLocalTransformationsIfNecessary());
    CHECK(isAlmostEqual(transformable_temp.localTransform(),
                        transformable.localTransform()));
}
