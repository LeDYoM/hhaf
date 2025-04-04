#include "catch_include.hpp"

#include <htypes/include/types.hpp>
// #include <haf/include/scene_nodes/transformable_scene_node.hpp>
#include <haf/include/scene/scene_node.hpp>
#include "matrix_utils.hpp"

using namespace haf;
using namespace haf::scene;
using namespace haf::scene::testing;
/*
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

TEST_CASE("haf::scene::Transformable check math", "[haf][scene][Transformable]")
{
    TransformableSceneNode transformable{nullptr, ""};
    transformable.Position = {3.0F, 3.0F};

    TransformableSceneNode transformable_temp{nullptr, ""};
    transformable_temp.Position = {2.0F, 2.0F};

    CHECK(transformable_temp.updateTransformIfNecessary());
    CHECK(transformable.updateTransformIfNecessary());
    CHECK_FALSE(isAlmostEqual(transformable_temp.localTransform(),
                              transformable.localTransform()));

    transformable.Position = {2.0F, 2.0F};
    CHECK(transformable.updateTransformIfNecessary());
    CHECK(isAlmostEqual(transformable_temp.localTransform(),
                        transformable.localTransform()));
}
*/
