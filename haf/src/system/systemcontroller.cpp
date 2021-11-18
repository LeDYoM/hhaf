#include "systemcontroller.hpp"
#include "window/window.hpp"
#include "simulation/simulation_system.hpp"
#include "input/inputsystem.hpp"
#include "scene/scenemanager.hpp"
#include "render/rendersystem.hpp"

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
    SystemProvider::init(std::move(iapp), backend_factory, argc, argv);
}

void SystemController::terminate()
{
    SystemProvider::terminate();
}

bool SystemController::preUpdate()
{
    const bool pre_update_wants_to_close{system<Window>().preLoop()};
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
    system<Window>().postLoop();

    return false;
}

}  // namespace haf::sys
