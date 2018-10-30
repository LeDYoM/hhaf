#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/components/statescontroller.hpp>

using namespace lib;
using namespace lib::scene;

TEST_CASE("lib::StatesController", "[StatesController]")
{
	constexpr u32 Start_State = 0U;
    struct CommonData
    {
        bool exit = false;
        u32 step{ 0U };
        sptr<StatesController<u32>> states_controller;
    };

    CommonData common;
    common.states_controller = msptr<StatesController<u32>>();

    common.states_controller->BeforeStart.connect([&common, Start_State](const auto& state)
	{
		CHECK(state == Start_State);
        CHECK(common.step == 0U);
        common.step++;
	});

    common.states_controller->StatePushed.connect([&common, Start_State](const auto& state)
    {
        CHECK(state == Start_State);
        common.states_controller->setState(1);
        CHECK(common.step == 1U);
        common.step++;

        common.states_controller->setState(1);

    });

    common.states_controller->StateStarted.connect([&common](const auto& state)
    {
        CHECK(state == 1);
        common.exit = true;
    });

    common.states_controller->StateFinished.connect([&common](const auto& state)
    {
        (void)state;
//        CHECK((state == 0) && (state == 1));
    });

    common.states_controller->start(Start_State);

    while (!common.exit)
    {
        common.states_controller->update();
    }
}
