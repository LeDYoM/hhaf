#include "system_controller.hpp"
#include "window/window_system.hpp"
#include "simulation/simulation_system.hpp"
#include "input/input_system.hpp"
#include "scene/scene_manager.hpp"
#include "time/time_system.hpp"
#include "debug_system/debug_system.hpp"
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

using namespace haf::core;

namespace haf::sys
{

SystemController::SystemController()  = default;
SystemController::~SystemController() = default;

void SystemController::init(
    rptr<IApp> iapp,
    rptr<host::IHostConnector> const host_connector,
    rptr<backend::BackendFactory> backend_factory,
    int const argc,
    char const* const argv[])
{
    (void)(host_connector);
    LogAsserter::log_assert(
        iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    SystemProvider::init(core::move(iapp), backend_factory, argc, argv);
}

void SystemController::terminate()
{
    SystemProvider::terminate();
}

bool SystemController::preUpdate()
{
    system<TimeSystem>().preUpdate();
    system<DebugSystem>().preUpdate();
    system<WindowSystem>().preUpdate();
    system<SimulationSystem>().preUpdate();
    system<InputSystem>().preUpdate();
    return system<WindowSystem>().exitRequested();
}

bool SystemController::update()
{
    system<InputSystem>().update();
    system<SimulationSystem>().update();
    system<scene::SceneManager>().update();
    system<DebugSystem>().update();
    system<WindowSystem>().update();
    return false;
}

bool SystemController::postUpdate()
{
    system<InputSystem>().postUpdate();
    system<WindowSystem>().postUpdate();
    system<DebugSystem>().postUpdate();
    system<TimeSystem>().postUpdate();

    return false;
}

}  // namespace haf::sys
