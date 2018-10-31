#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/sceneController.hpp>

TEST_CASE("lib::scene::SceneController", "[lib][SceneController]")
{
    using namespace lib;
    using namespace lib::scene;

    struct CommonData
    {
        bool exit = false;
        u32 step{ 0U };
        sptr<SceneController> scene_controller;
    };

    CommonData common;
    common.scene_controller = msptr<SceneController>();

    common.states_controller->BeforeStart.connect([&common]()
	{
        CHECK(common.step == 0U);
        common.step++;
        CHECK(common.step == 1U);
    });

    common.states_controller->StatePushed.connect([&common, Start_State](const auto& state)
    {
        CHECK(state == Start_State);
        common.step++;
        CHECK(common.step == 2U);
    });

    common.states_controller->StatePopped.connect([&common, Finish_State](const auto& state)
    {
        CHECK(state == Finish_State);
        common.step++;
        CHECK(common.step == 7U);
    });

    common.states_controller->AfterFinish.connect([&common]()
    {
        common.step++;
        CHECK(common.step == 8U);
        common.exit = true;
    });


    common.states_controller->StateStarted.connect([&common, Start_State, Finish_State](const auto& state)
    {
        if (common.step == 2U)
        {
            CHECK(state == Start_State);
            common.step++;
            CHECK(common.step == 3U);
            common.states_controller->setState(Finish_State);
        }
        else
        {
            CHECK(state == Finish_State);
            common.step++;
            CHECK(common.step == 5U);
            common.states_controller->pop_state();
        }

    });

    common.states_controller->StateFinished.connect([&common, Start_State, Finish_State](const auto& state)
    {
        if (common.step == 3U)
        {
            CHECK(state == Start_State);
            common.step++;
            CHECK(common.step == 4U);
        }
        else
        {
            CHECK(state == Finish_State);
            common.step++;
            CHECK(common.step == 6U);
            common.states_controller->pop_state();
        }
    });

    common.states_controller->start(Start_State);

    while (!common.exit)
    {
        common.states_controller->update();
    }

    common.step++;
    CHECK(common.step == 9U);
}
