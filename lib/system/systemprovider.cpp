#include "systemprovider.hpp"

#include <backend/include/backendfactory.hpp>
#include <lib/system/filesystem.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/system/randomsystem.hpp>
#include <lib/system/rendersystem.hpp>
#include <lib/system/scenemanager.hpp>
#include <lib/system/window.hpp>
#include <lib/system/timesystem.hpp>

#include <lib/resources/include/resourcemanager.hpp>
#include <lib/simulation/simulationsystem.hpp>

#include <lib/include/liblog.hpp>
#include <hosted_app/include/iapp.hpp>

namespace lib::sys
{
struct SystemProvider::SystemProviderPrivate
{
    SystemProviderPrivate() = default;
    ~SystemProviderPrivate() = default;

    IApp *app_;
    uptr<backend::BackendFactory> backend_factory_;
    uptr<Window> window_;
    uptr<ResourceManager> resource_manager_;
    uptr<InputSystem> input_system_;
    uptr<scene::SceneManager> scene_manager_;
    uptr<RandomSystem> random_system_;
    uptr<FileSystem> file_system_;
    uptr<TimeSystem> time_system_;
    uptr<RenderSystem> render_system_;
#ifdef LIB_COMPILE_SIMULATIONS
    uptr<SimulationSystem> simulation_system_;
#endif
};

SystemProvider::SystemProvider()
    : p_{muptr<SystemProviderPrivate>()} {}

SystemProvider::~SystemProvider() = default;

void SystemProvider::init(IApp *iapp)
{
    log_assert(iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    p_->app_ = iapp;
    p_->backend_factory_ = muptr<backend::BackendFactory>();
    p_->time_system_ = muptr<TimeSystem>();
    p_->window_ = muptr<Window>(*this);
    p_->input_system_ = muptr<InputSystem>(p_->window_->inputDriver());
    p_->scene_manager_ = muptr<scene::SceneManager>(*this);
    p_->resource_manager_ = muptr<sys::ResourceManager>(*this);
    p_->render_system_ = muptr<sys::RenderSystem>(*this);
    p_->random_system_ = muptr<RandomSystem>(*this);
    p_->file_system_ = muptr<FileSystem>(*this);
#ifdef LIB_COMPILE_SIMULATIONS
    p_->simulation_system_ = muptr<SimulationSystem>(*this);
    p_->simulation_system_->initialize();
#endif
}

void SystemProvider::terminate()
{
    p_->scene_manager_->finish();
    p_->simulation_system_ = nullptr;
    p_->file_system_ = nullptr;
    p_->random_system_ = nullptr;
    p_->render_system_ = nullptr;
    p_->resource_manager_ = nullptr;
    p_->scene_manager_ = nullptr;
    p_->input_system_ = nullptr;
    p_->window_ = nullptr;
    p_->time_system_ = nullptr;
    p_->backend_factory_ = nullptr;
}

IApp &SystemProvider::app()
{
    return *p_->app_;
}

const IApp &SystemProvider::app() const
{
    return *p_->app_;
}

const Window &SystemProvider::parentWindow() const noexcept
{
    return *p_->window_;
}

Window &SystemProvider::parentWindow() noexcept
{
    return *p_->window_;
}

const ResourceManager &SystemProvider::resourceManager() const noexcept
{
    return *p_->resource_manager_;
}

ResourceManager &SystemProvider::resourceManager() noexcept
{
    return *p_->resource_manager_;
}

const sys::InputSystem &SystemProvider::inputSystem() const noexcept
{
    return *p_->input_system_;
}

sys::InputSystem &SystemProvider::inputSystem() noexcept
{
    return *p_->input_system_;
}

const RandomSystem &SystemProvider::randomSystem() const noexcept
{
    return *p_->random_system_;
}

RandomSystem &SystemProvider::randomSystem() noexcept
{
    return *p_->random_system_;
}

const FileSystem &SystemProvider::fileSystem() const noexcept
{
    return *p_->file_system_;
}

FileSystem &SystemProvider::fileSystem() noexcept
{
    return *p_->file_system_;
}

const scene::SceneManager &SystemProvider::sceneManager() const noexcept
{
    return *p_->scene_manager_;
}

scene::SceneManager &SystemProvider::sceneManager() noexcept
{
    return *p_->scene_manager_;
}

#ifdef LIB_COMPILE_SIMULATIONS
const SimulationSystem &SystemProvider::simulationSystem() const noexcept
{
    return *p_->simulation_system_;
}

SimulationSystem &SystemProvider::simulationSystem() noexcept
{
    return *p_->simulation_system_;
}
#endif

const TimeSystem &SystemProvider::timeSystem() const noexcept
{
    return *p_->time_system_;
}

TimeSystem &SystemProvider::timeSystem() noexcept
{
    return *p_->time_system_;
}

const backend::BackendFactory &SystemProvider::backendFactory() const noexcept
{
    return *p_->backend_factory_;
}

backend::BackendFactory &SystemProvider::backendFactory() noexcept
{
    return *p_->backend_factory_;
}

const RenderSystem &SystemProvider::renderSystem() const noexcept
{
    return *p_->render_system_;
}

RenderSystem &SystemProvider::renderSystem() noexcept
{
    return *p_->render_system_;
}

bool SystemProvider::runStep()
{
    const bool windowWants2Close{parentWindow().preLoop()};
#ifdef LIB_COMPILE_SIMULATIONS
    simulationSystem().update();
#endif
    inputSystem().update();
    sceneManager().update();

    parentWindow().postLoop();
    return windowWants2Close;
}
} // namespace lib::sys
