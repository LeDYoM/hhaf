#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <haf/include/scene_components/statescontroller.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;

TEST_CASE("haf::StatesControllerComponent",
          "[StatesControllerComponent][lib][scene][component][StatesControllerComponent]")
{
    constexpr u32 Start_State  = 0U;
    constexpr u32 Finish_State = 1U;

    struct CommonData
    {
        bool exit = false;
        u32 step{0U};
        sptr<StatesControllerComponent<u32>> states_controller;
    };

    CommonData common;
    common.states_controller = msptr<StatesControllerComponent<u32>>();

    common.states_controller->BeforeStart.connect([&common]() {
        CHECK(common.step == 0U);
        common.step++;
        CHECK(common.step == 1U);
    });

    common.states_controller->StatePushed.connect(
        [&common, Start_State](const auto& state) {
            CHECK(state == Start_State);
            common.step++;
            CHECK(common.step == 2U);
        });

    common.states_controller->StatePopped.connect(
        [&common, Finish_State](const auto& state) {
            CHECK(state == Finish_State);
            common.step++;
            CHECK(common.step == 7U);
        });

    common.states_controller->AfterFinish.connect([&common]() {
        common.step++;
        CHECK(common.step == 8U);
        common.exit = true;
    });

    common.states_controller->StateStarted.connect(
        [&common, Start_State, Finish_State](const auto& state) {
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

    common.states_controller->StateFinished.connect(
        [&common, Start_State, Finish_State](const auto& state) {
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
