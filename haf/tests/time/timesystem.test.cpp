#include "catch.hpp"

#include <htypes/include/types.hpp>
#include <time/i_include/timesystem.hpp>
#include <haf/time/include/timepoint.hpp>
#include <system/i_include/systembase.hpp>
#include <system/i_include/systemprovider.hpp>
#include "system_test_utils.hpp"

#include <thread>

using namespace htps;
using namespace haf;
using namespace haf::sys;
using namespace haf::time;

TEST_CASE("TimeSystem", "[haf][timesystem]")
{
    auto test_time_system = makeTestSystem<TestTimeSystem>();
    haf::sys::TimeSystem& time_system =
        test_time_system->system<TimeSystem>();

    TimePoint const time_now = time_system.now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
    TimePoint const after = time_system.now();

    CHECK(after >= time_now);
    CHECK(after.milliseconds() - time_now.milliseconds() >= TimePoint::Rep{10U});

}
