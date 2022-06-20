#include "system_controller.hpp"
#include "window/window_system.hpp"
#include "simulation/simulation_system.hpp"
#include "input/input_system.hpp"
#include "scene/scene_manager.hpp"
#include "render/render_system.hpp"
#include "time/time_system.hpp"

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
    const bool pre_update_wants_to_close{system<WindowSystem>().preLoop(
        system<TimeSystem>().timeSinceStart())};
    system<SimulationSystem>().updateSimulationInput();
    system<InputSystem>().preUpdate();
    return pre_update_wants_to_close;
}

bool SystemController::update()
{
    system<InputSystem>().update();
    system<SimulationSystem>().updateSimulationOutput();
    system<scene::SceneManager>().update();
    system<RenderSystem>().update();

    return false;
}

bool SystemController::postUpdate()
{
    system<InputSystem>().postUpdate();
    system<WindowSystem>().postLoop();

    return false;
}

}  // namespace haf::sys
