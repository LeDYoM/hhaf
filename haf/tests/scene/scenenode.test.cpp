#include "catch.hpp"

#include <haf/include/core/types.hpp>
#include <haf/include/scene/scene_node.hpp>

#include "system_test_utils.hpp"

using namespace haf;
using namespace haf::test;

TEST_CASE("Constructor", "[SceneNode]")
{
    using namespace haf;
    using namespace haf::scene;

    auto test_scene_manager{makeTestSystem<TestSceneManager>()};
    SceneManager& scene_manager{test_scene_manager->system<SceneManager>()};
    (void)(scene_manager);
}
