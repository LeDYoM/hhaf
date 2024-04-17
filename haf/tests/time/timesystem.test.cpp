#include "catch.hpp"

#include <htypes/include/types.hpp>
#include "time/time_system.hpp"
#include <haf/include/time/time_point.hpp>
#include "system/system_base.hpp"
#include "system/system_provider.hpp"
#include "system_test_utils.hpp"

#include <thread>

using namespace htps;
using namespace haf;
using namespace haf::test;
using namespace haf::sys;
using namespace haf::time;

TEST_CASE("TimeSystem", "[haf][timesystem]")
{
    auto test_time_system{makeTestSystem<TestTimeSystem>()};
    auto& time_system = test_time_system->system<TimeSystem>();
    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
    CHECK(time_system.now() != TimePoint{});
}

TEST_CASE("TimeSystem::now", "[haf][timesystem]")
{
    auto test_time_system{makeTestSystem<TestTimeSystem>()};
    auto& time_system = test_time_system->system<TimeSystem>();

    TimePoint const time_now = time_system.now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
    TimePoint const after = time_system.now();

    CHECK(after >= time_now);
    CHECK(after.milliseconds() - time_now.milliseconds() >=
          TimePoint::Rep{10U});
}

TEST_CASE("TimeSystem frame time", "[haf][timesystem]")
{
    auto test_time_system{makeTestSystem<TestTimeSystem>()};
    auto& time_system = test_time_system->system<TimeSystem>();

    time_system.preUpdate();
    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
    time_system.postUpdate();
    std::this_thread::sleep_for(std::chrono::milliseconds(10U));
    time_system.preUpdate();

    CHECK(time_system.lastFrameTime().milliseconds() > TimePoint::Rep{10U});
}
