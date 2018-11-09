#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/sceneController.hpp>

TEST_CASE("lib::scene::SceneController", "[lib][SceneController]")
{
    using namespace lib;
    using namespace lib::scene;

    class UniqueScene : public Scene
    {
    public:
        UniqueScene() : Scene{str("UniqueScene_Test")} {}

        void onCreated() override
        {

        }
    };

    struct CommonData
    {
        bool exit = false;
        u32 step{ 0U };
        sptr<SceneController> scene_controller = msptr<SceneController>();
    };

    CommonData common;
    common.scene_controller = msptr<SceneController>();

    common.scene_controller->startScene<UniqueScene>();

    while (!common.exit)
    {
        common.scene_controller->update();
        common.exit = true;
    }

    common.step++;
    CHECK(common.step == 1U);
}
