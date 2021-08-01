#include "systemcontroller.hpp"
#include "window/window.hpp"
#include "simulation/simulationsystem.hpp"
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

void SystemController::init(rptr<IApp> iapp,
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

bool SystemController::runStep()
{
    const bool windowWants2Close{window().preLoop()};
    simulationSystem().update();
    inputSystem().update();
    sceneManager().update();
    renderSystem().update();

    window().postLoop();
    return windowWants2Close;
}
}  // namespace haf::sys
