#include "systemcontroller.hpp"
#include <window/i_include/window.hpp>
#include <haf/simulation/include/simulationsystem.hpp>
#include <input/i_include/inputsystem.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <render/i_include/rendersystem.hpp>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

using namespace mtps;

namespace haf::sys
{

SystemController::SystemController() = default;
SystemController::~SystemController() = default;

void SystemController::init(rptr<IApp> iapp)
{
    LogAsserter::log_assert(
        iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    SystemProvider::init(std::move(iapp));
}

void SystemController::terminate()
{
    SystemProvider::terminate();
}

bool SystemController::runStep()
{
    const bool windowWants2Close{parentWindow().preLoop()};
    simulationSystem().update();
    inputSystem().update();
    sceneManager().update();
    renderSystem().update();

    parentWindow().postLoop();
    return windowWants2Close;
}
}  // namespace haf::sys
