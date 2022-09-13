#include "system_controller.hpp"
#include "window/window_system.hpp"
#include "simulation/simulation_system.hpp"
#include "input/input_system.hpp"
#include "scene/scene_manager.hpp"
#include "render/render_system.hpp"
#include "time/time_system.hpp"
#include "debug_system/debug_system.hpp"
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

using namespace htps;

namespace haf::sys
{

SystemController::SystemController()  = default;
SystemController::~SystemController() = default;

void SystemController::init(
    rptr<IApp> iapp,
    htps::rptr<host::IHostConnector> const host_connector,
    rptr<backend::BackendFactory> backend_factory,
    int const argc,
    char const* const argv[])
{
    (void)(host_connector);
    LogAsserter::log_assert(
        iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    SystemProvider::init(htps::move(iapp), backend_factory, argc, argv);
}

void SystemController::terminate()
{
    SystemProvider::terminate();
}

bool SystemController::preUpdate()
{
    system<TimeSystem>().startFrame();
    system<DebugSystem>().onStartPreUpdate();
    const bool pre_update_wants_to_close{system<WindowSystem>().preLoop()};
    system<SimulationSystem>().updateSimulationInput();
    system<InputSystem>().preUpdate();
    system<DebugSystem>().onFinishPreUpdate();
    return pre_update_wants_to_close;
}

bool SystemController::update()
{
    system<DebugSystem>().onStartUpdate();
    system<InputSystem>().update();
    system<SimulationSystem>().updateSimulationOutput();
    system<scene::SceneManager>().update();
    system<RenderSystem>().update();
    system<DebugSystem>().onFinishUpdate();

    return false;
}

bool SystemController::postUpdate()
{
    system<DebugSystem>().onStartPostUpdate();
    system<InputSystem>().postUpdate();
    system<WindowSystem>().postLoop();
    system<DebugSystem>().onFinishPostUpdate();
    system<TimeSystem>().endFrame();

    return false;
}

}  // namespace haf::sys
