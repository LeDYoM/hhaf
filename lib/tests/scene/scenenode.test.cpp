#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/include/scenenode.hpp>
#include <lib/scene/include/scene.hpp>

auto unitTestScene()
{
    static auto uts(lib::msptr<lib::scene::Scene>("unitTest"));
    return uts;
}

TEST_CASE("Constructor", "[SceneNode]")
{
    using namespace lib;
    using namespace lib::scene;

    auto node_test(unitTestScene()->createSceneNode("SceneNode_test"));
    CHECK(unitTestScene()->sceneNodes().size() == 1U);
    CHECK(node_test->sceneNodes().size() == 0U);
}
