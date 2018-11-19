#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/scene.hpp>
#include <lib/scene/scenecontroller.hpp>
#include <lib/include/scene/iscene.hpp>

struct CommonData
{
    bool exit = false;
    lib::u32 step{ 0U };
    lib::sptr<lib::scene::SceneController> scene_controller = lib::msptr<lib::scene::SceneController>();
};

CommonData common;

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
        common.scene_controller->terminateScene();
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
        common.scene_controller->setSceneDirector([](const str&scene_name)
        {
            CHECK(str(scene_name) == GroupScene1::StaticTypeName);
            return str(GroupScene2::StaticTypeName);
        });
        CHECK(common.scene_controller->registerSceneType<GroupScene1>());
        CHECK(common.scene_controller->registerSceneType<GroupScene2>());
        CHECK_FALSE(common.scene_controller->registerSceneType<GroupScene1>());
        CHECK_FALSE(common.scene_controller->registerSceneType<GroupScene2>());

        common.scene_controller->startScene<GroupScene1>();

        common.scene_controller->update();
        CHECK(common.scene_controller->currentState()->name() == GroupScene1::StaticTypeName);
        common.scene_controller->update();
        CHECK(common.scene_controller->currentState()->name() == GroupScene2::StaticTypeName);
    }
}
