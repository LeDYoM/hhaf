#include "catch.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/components/statescontroller.hpp>

using namespace lib;
using namespace lib::scene;

TEST_CASE("lib::StatesController", "[StatesController]")
{
	constexpr u32 Start_State = 0U;
    bool exit = false;
    sptr<StatesController<u32>> states_controller(msptr<StatesController<u32>>());

	states_controller->BeforeStart.connect([Start_State](const auto& state)
	{
		CHECK(state == Start_State);
	});

    states_controller->StateStarted.connect([Start_State,&exit](const auto& state)
    {
        CHECK(state == Start_State);
        exit = true;
    });

	states_controller->start(Start_State);

    while (!exit)
    {
        states_controller->update();
    }
}
