#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene.hpp>

using namespace htps;

auto unitTestScene()
{
    static auto uts(msptr<haf::scene::Scene>("unitTest"));
    return uts;
}

TEST_CASE("Constructor", "[SceneNode]")
{
    using namespace haf;
    using namespace haf::scene;

    auto node_test(unitTestScene()->createSceneNode("SceneNode_test"));
    CHECK(unitTestScene()->sceneNodes().size() == 1U);
    CHECK(node_test->sceneNodes().size() == 0U);
}
