#include "catch_include.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene_components/transformation.hpp>

TEST_CASE("haf::scene::Transformation", "[haf][scene][Transformation]")
{
    using namespace haf;
    using namespace haf::scene;

    Transformation transformation;
    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.Position = {2.0F, 4.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.Scale = {2.0F, 4.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());

    transformation.Rotation = {2.0F};

    CHECK(transformation.updateTransformIfNecessary());
    CHECK_FALSE(transformation.updateTransformIfNecessary());
}
