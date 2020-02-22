#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

#include <lib/scene/include/scene.hpp>
#include <lib/scene/include/scenecontroller.hpp>

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
    static constexpr char StaticTypeName[] = "UniqueScene";
    UniqueScene() : Scene{StaticTypeName} {}
};

class GroupScene1 : public lib::scene::Scene
{
public:
    static constexpr char StaticTypeName[] = "GroupScene1";
    GroupScene1() : Scene{StaticTypeName} {}

    void onCreated() override
    {
        ++(common.step);
    }

    void update() override
    {
        ++(common.step);
        common.scene_controller->switchToNextScene();
    }
};

class GroupScene2 : public lib::scene::Scene
{
public:
    static constexpr char StaticTypeName[] = "GroupScene2";
    GroupScene2() : Scene{StaticTypeName} {}

    void onCreated() override
    {
        ++(common.step);
    }

    void update() override
    {
        ++(common.step);
        common.scene_controller->switchToNextScene();
    }
};

TEST_CASE("SceneController", "[lib][SceneController]")
{
    using namespace lib;
    using namespace lib::scene;

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
            if (str(scene_name) == GroupScene1::StaticTypeName)
            {
                return str(GroupScene2::StaticTypeName);
            }
            else if (str(scene_name) == GroupScene2::StaticTypeName)
            {
                return str("");
            }
            CHECK(false);
            return str("");
        });
        CHECK(common.scene_controller->registerSceneNodeType<GroupScene1>());
        CHECK(common.scene_controller->registerSceneNodeType<GroupScene2>());
        CHECK_FALSE(common.scene_controller->registerSceneNodeType<GroupScene1>());
        CHECK_FALSE(common.scene_controller->registerSceneNodeType<GroupScene2>());

        common.step = 0U;
        common.scene_controller->startScene<GroupScene1>();
        CHECK(common.scene_controller->currentScene()->name() == GroupScene1::StaticTypeName);
        CHECK(common.step == 1U);

        // Update triggers finish and creation of new scene.
        common.scene_controller->update();
        CHECK(common.scene_controller->currentScene()->name() == GroupScene2::StaticTypeName);
        CHECK(common.step == 3U);

        common.scene_controller->update();
        CHECK(common.scene_controller->currentSceneIsNull());
        CHECK(common.step == 4U);
        CHECK_FALSE(common.scene_controller->isActive());
        common.scene_controller->update();
        CHECK(common.scene_controller->currentSceneIsNull());
        CHECK_FALSE(common.scene_controller->isActive());
        CHECK(common.step == 4U);
    }
}
