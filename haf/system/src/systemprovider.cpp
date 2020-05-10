#include "systemprovider.hpp"

#include <backend/include/backendfactory.hpp>
#include <backend/include/backend_creator.hpp>
#include <haf/filesystem/i_include/filesystem.hpp>
#include <haf/input/i_include/inputsystem.hpp>
#include <haf/random/i_include/randomsystem.hpp>
#include <haf/render/i_include/rendersystem.hpp>
#include <haf/scene/i_include/scenemanager.hpp>
#include <haf/window/i_include/window.hpp>
#include <haf/time/i_include/timesystem.hpp>
#include <haf/shareddata/i_include/shareddatasystem.hpp>
#include <haf/resources/i_include/resourcemanager.hpp>
#include <haf/simulation/include/simulationsystem.hpp>

#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

#include <functional>

using namespace mtps;

namespace haf::sys
{
struct SystemProvider::SystemProviderPrivate
{
    SystemProviderPrivate()  = default;
    ~SystemProviderPrivate() = default;

    IApp* app_;
    uptr<SharedDataSystem> shared_data_system_;
    uptr<backend::BackendFactory, void (*)(haf::backend::BackendFactory*)>
        backend_factory_{nullptr, nullptr};
    uptr<Window> window_;
    uptr<ResourceManager> resource_manager_;
    uptr<InputSystem> input_system_;
    uptr<scene::SceneManager> scene_manager_;
    uptr<RandomSystem> random_system_;
    uptr<FileSystem> file_system_;
    uptr<TimeSystem> time_system_;
    uptr<RenderSystem> render_system_;
    uptr<SimulationSystem> simulation_system_;
    bool exit_requested_{false};
};

SystemProvider::SystemProvider() : p_{muptr<SystemProviderPrivate>()}
{}

SystemProvider::~SystemProvider() = default;

void SystemProvider::init(IApp* iapp)
{
    LogAsserter::log_assert(iapp != nullptr,
               "Cannot create a SystemProvider with a nullptr app");
    p_->backend_factory_ =
        uptr<backend::BackendFactory, void (*)(haf::backend::BackendFactory*)>(
            createBackendFactory(), destroyBackendFactory);
    p_->app_                = iapp;
    p_->shared_data_system_ = muptr<SharedDataSystem>(*this);
    p_->time_system_        = muptr<TimeSystem>(*this);
    p_->window_             = muptr<Window>(*this);
    p_->input_system_       = muptr<InputSystem>(*this);
    p_->scene_manager_      = muptr<scene::SceneManager>(*this);
    p_->resource_manager_   = muptr<sys::ResourceManager>(*this);
    p_->render_system_      = muptr<sys::RenderSystem>(*this);
    p_->random_system_      = muptr<RandomSystem>(*this);
    p_->file_system_        = muptr<FileSystem>(*this);
    p_->simulation_system_ = muptr<SimulationSystem>(*this);
    p_->simulation_system_->initialize();

    p_->window_->create(nullptr);
    p_->render_system_->setRenderTarget(p_->window_->renderTarget());
    p_->input_system_->setInputDriver(p_->window_->inputDriver());
    p_->app_->onInit(*this);
}

void SystemProvider::requestExit()
{
    p_->exit_requested_ = true;
}

bool SystemProvider::exitRequested() const
{
    return p_->exit_requested_;
}

void SystemProvider::terminate()
{
    p_->app_->onFinish(*this);
    p_->scene_manager_->finish();
    p_->scene_manager_     = nullptr;
    p_->simulation_system_ = nullptr;
    p_->file_system_       = nullptr;
    p_->random_system_     = nullptr;
    p_->render_system_     = nullptr;
    p_->resource_manager_  = nullptr;
    p_->scene_manager_     = nullptr;
    p_->input_system_      = nullptr;
    p_->window_            = nullptr;
    p_->time_system_       = nullptr;
    p_->backend_factory_   = nullptr;
}

IApp& SystemProvider::app()
{
    return *p_->app_;
}

const IApp& SystemProvider::app() const
{
    return *p_->app_;
}

const Window& SystemProvider::parentWindow() const noexcept
{
    return *p_->window_;
}

Window& SystemProvider::parentWindow() noexcept
{
    return *p_->window_;
}

const ResourceManager& SystemProvider::resourceManager() const noexcept
{
    return *p_->resource_manager_;
}

ResourceManager& SystemProvider::resourceManager() noexcept
{
    return *p_->resource_manager_;
}

const sys::InputSystem& SystemProvider::inputSystem() const noexcept
{
    return *p_->input_system_;
}

sys::InputSystem& SystemProvider::inputSystem() noexcept
{
    return *p_->input_system_;
}

const RandomSystem& SystemProvider::randomSystem() const noexcept
{
    return *p_->random_system_;
}

RandomSystem& SystemProvider::randomSystem() noexcept
{
    return *p_->random_system_;
}

const FileSystem& SystemProvider::fileSystem() const noexcept
{
    return *p_->file_system_;
}

FileSystem& SystemProvider::fileSystem() noexcept
{
    return *p_->file_system_;
}

const scene::SceneManager& SystemProvider::sceneManager() const noexcept
{
    return *p_->scene_manager_;
}

scene::SceneManager& SystemProvider::sceneManager() noexcept
{
    return *p_->scene_manager_;
}

const SimulationSystem& SystemProvider::simulationSystem() const noexcept
{
    return *p_->simulation_system_;
}

SimulationSystem& SystemProvider::simulationSystem() noexcept
{
    return *p_->simulation_system_;
}

const TimeSystem& SystemProvider::timeSystem() const noexcept
{
    return *p_->time_system_;
}

TimeSystem& SystemProvider::timeSystem() noexcept
{
    return *p_->time_system_;
}

const backend::BackendFactory& SystemProvider::backendFactory() const noexcept
{
    return *p_->backend_factory_;
}

backend::BackendFactory& SystemProvider::backendFactory() noexcept
{
    return *p_->backend_factory_;
}

const RenderSystem& SystemProvider::renderSystem() const noexcept
{
    return *p_->render_system_;
}

RenderSystem& SystemProvider::renderSystem() noexcept
{
    return *p_->render_system_;
}

ISharedDataSystem& SystemProvider::sharedDataSystem() noexcept
{
    return *p_->shared_data_system_;
}

const ISharedDataSystem& SystemProvider::sharedDataSystem() const noexcept
{
    return *p_->shared_data_system_;
}

bool SystemProvider::runStep()
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