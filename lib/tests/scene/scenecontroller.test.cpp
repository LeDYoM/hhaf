#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/scene.hpp>
#include <lib/scene/scenecontroller.hpp>
#include <lib/include/scene/iscene.hpp>
#include <lib/scene/scenemanager.hpp>

class UniqueScene : public lib::scene::Scene
{
public:
    DECLARE_SCENE(UniqueScene)
};

enum class SceneState
{
    Created = 0U,
    Finished
};

class GroupScene1 : public lib::scene::Scene
{
public:
    DECLARE_SCENE(GroupScene1)

    void onCreated() override
    {

    }

    void updateScene() override
    {
        sceneManager().sceneController()->terminateScene();
    }
};

class GroupScene2 : public lib::scene::Scene
{
public:
    DECLARE_SCENE(GroupScene2)
};

TEST_CASE("SceneController", "[lib][SceneController]")
{
    using namespace lib;
    using namespace lib::scene;

    enum class TestScenesState
    {
        Created = 0U,
        Update
    };

    struct CommonData
    {
        bool exit = false;
        u32 step{ 0U };
        sptr<SceneController> scene_controller = msptr<SceneController>();
    };

    CommonData common;

    SECTION("Simple scene")
    {
        CHECK(common.scene_controller->registerAndStartScene<UniqueScene>("UniqueScene"));

        while (!common.exit)
        {
            common.scene_controller->update();
            common.exit = true;
        }

        common.step++;
        CHECK(common.step == 1U);
    }

    SECTION("Two scenes")
    {
        CHECK(common.scene_controller->registerSceneType<GroupScene1>());
        CHECK(common.scene_controller->registerSceneType<GroupScene2>());
        CHECK_FALSE(common.scene_controller->registerSceneType<GroupScene1>());
        CHECK_FALSE(common.scene_controller->registerSceneType<GroupScene2>());

        common.scene_controller->startScene<GroupScene1>();

        common.scene_controller->update();
        CHECK(common.scene_controller->currentState()->name() == GroupScene1::StaticTypeName);
    }
}
