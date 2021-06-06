#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene/scenenode.hpp>
#include <haf/include/scene/scene.hpp>
#include "scene/scenemanager.hpp"
#include "system_test_utils.hpp"

TEST_CASE("haf::scene::SceneManager", "[haf][scene][scenemanager]")
{
    using namespace haf;
    using namespace haf::scene;

    auto test_scene_manager = makeTestSystem<TestSceneManager>();
    SceneManager& scene_manager =
        test_scene_manager->system<SceneManager>();

    CHECK(&scene_manager != nullptr);
}
