#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

#include <haf/scene/include/scene.hpp>
#include <scene/i_include/scenecontroller.hpp>

using namespace mtps;

struct CommonData
{
    bool exit = false;
    u32 step{0U};
    sptr<haf::scene::SceneController> scene_controller =
        msptr<haf::scene::SceneController>();
};

CommonData common;

class UniqueScene : public haf::scene::Scene
{
public:
    static constexpr char StaticTypeName[] = "UniqueScene";
    UniqueScene() : Scene{StaticTypeName} {}
};

class GroupScene1 : public haf::scene::Scene
{
public:
    static constexpr char StaticTypeName[] = "GroupScene1";
    GroupScene1() : Scene{StaticTypeName} {}

    void onCreated() override { ++(common.step); }

    virtual mtps::str nextSceneName() { return "GroupScene2"; }
    void update() override
    {
        ++(common.step);
        common.scene_controller->switchToNextScene();
    }
};

class GroupScene2 : public haf::scene::Scene
{
public:
    static constexpr char StaticTypeName[] = "GroupScene2";
    GroupScene2() : Scene{StaticTypeName} {}

    void onCreated() override { ++(common.step); }

    void update() override
    {
        ++(common.step);
        common.scene_controller->switchToNextScene();
    }
};

TEST_CASE("SceneController", "[lib][SceneController]")
{
    using namespace haf;
    using namespace haf::scene;

    SECTION("Simple scene")
    {
        CHECK(common.scene_controller->registerAndStartScene<UniqueScene>(
            "UniqueScene"));

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
        CHECK(common.scene_controller->registerSceneNodeType<GroupScene1>());
        CHECK(common.scene_controller->registerSceneNodeType<GroupScene2>());
        CHECK_FALSE(
            common.scene_controller->registerSceneNodeType<GroupScene1>());
        CHECK_FALSE(
            common.scene_controller->registerSceneNodeType<GroupScene2>());

        common.step = 0U;
        common.scene_controller->startScene<GroupScene1>();
        CHECK(common.scene_controller->currentScene()->name() ==
              GroupScene1::StaticTypeName);
        CHECK(common.step == 1U);

        common.scene_controller->update();
        CHECK(common.scene_controller->currentScene()->name() ==
              GroupScene1::StaticTypeName);
        CHECK(common.step == 2U);

        // Update triggers finish and creation of new scene.
        common.scene_controller->update();
        CHECK(common.scene_controller->currentScene()->name() ==
              GroupScene2::StaticTypeName);
        CHECK_FALSE(common.scene_controller->currentSceneIsNull());
        CHECK(common.step == 4U);
        CHECK(common.scene_controller->isActive());

        // Now the scene is finish and no new scene is added
        common.scene_controller->update();
        CHECK(common.scene_controller->currentSceneIsNull());
        CHECK_FALSE(common.scene_controller->isActive());
        CHECK(common.step == 4U);

        CHECK(common.scene_controller->unregisterSceneNodeType<GroupScene1>());
        CHECK(common.scene_controller->unregisterSceneNodeType<GroupScene2>());
        CHECK_FALSE(
            common.scene_controller->unregisterSceneNodeType<GroupScene1>());
        CHECK_FALSE(
            common.scene_controller->unregisterSceneNodeType<GroupScene2>());
    }

    SECTION("Two scenes: Error unregistered scene")
    {
        CHECK(common.scene_controller->registerSceneNodeType<GroupScene1>());
        CHECK_FALSE(
            common.scene_controller->registerSceneNodeType<GroupScene1>());

        common.step = 0U;
        common.scene_controller->startScene<GroupScene1>();
        CHECK(common.scene_controller->currentScene()->name() ==
              GroupScene1::StaticTypeName);
        CHECK(common.step == 1U);

        common.scene_controller->update();
        CHECK(common.scene_controller->currentScene()->name() ==
              GroupScene1::StaticTypeName);
        CHECK(common.step == 2U);

        // Update triggers finish and creation of new scene.
        common.scene_controller->update();
        CHECK(common.scene_controller->currentSceneIsNull());
        CHECK(common.step == 2U);
        CHECK_FALSE(common.scene_controller->isActive());

        CHECK(common.scene_controller->unregisterSceneNodeType<GroupScene1>());
        CHECK_FALSE(
            common.scene_controller->unregisterSceneNodeType<GroupScene1>());
        CHECK_FALSE(
            common.scene_controller->unregisterSceneNodeType<GroupScene2>());
    }
}
