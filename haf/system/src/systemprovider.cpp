#include <system/i_include/systemprovider.hpp>

#include <backend/include/backendfactory.hpp>
#include <backend/include/backend_creator.hpp>
#include <filesystem/i_include/filesystem.hpp>
#include <input/i_include/inputsystem.hpp>
#include <random/i_include/randomsystem.hpp>
#include <render/i_include/rendersystem.hpp>
#include <scene/i_include/scenemanager.hpp>
#include <window/i_include/window.hpp>
#include <time/i_include/timesystem.hpp>
#include <shareddata/i_include/shareddatasystem.hpp>
#include <resources/i_include/resourcemanager.hpp>
#include <simulation/i_include/simulationsystem.hpp>

#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

#include <haf/system/include/datawrappercreator.hpp>
#include <haf/system/include/systemaccess.hpp>
#include <functional>

using namespace mtps;

namespace haf::sys
{
struct SystemProvider::SystemProviderPrivate final
{
    rptr<IApp> app_;
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
};

SystemProvider::SystemProvider() : p_{muptr<SystemProviderPrivate>()}
{}

SystemProvider::~SystemProvider() = default;

void SystemProvider::fastInit(InitSystemOptions const& init_system_options)
{
    if (init_system_options.init_shared_data_system)
    {
        DisplayLog::debug("Initializing SharedDataSystem");
        p_->shared_data_system_ = muptr<SharedDataSystem>(*this);
    }

    if (init_system_options.init_time_system)
    {
        DisplayLog::debug("Initializing Time System");
        p_->time_system_ = muptr<TimeSystem>(*this);
    }

    if (init_system_options.init_window_system)
    {
        DisplayLog::debug("Initializing Window");
        p_->window_ = muptr<Window>(*this);
    }

    if (init_system_options.init_input_system)
    {
        DisplayLog::debug("Initializing Input System");
        p_->input_system_ = muptr<InputSystem>(*this);
    }

    if (init_system_options.init_scene_manager)
    {
        DisplayLog::debug("Initializing Scene Manager");
        p_->scene_manager_ = muptr<scene::SceneManager>(*this);
    }

    if (init_system_options.init_resource_manager)
    {
        DisplayLog::debug("Initializing Resource Manager");
        p_->resource_manager_ = muptr<sys::ResourceManager>(*this);
    }

    if (init_system_options.init_render_system)
    {
        DisplayLog::debug("Initializing Render System");
        p_->render_system_ = muptr<sys::RenderSystem>(*this);
    }

    if (init_system_options.init_random_system)
    {
        DisplayLog::debug("Initializing Random System");
        p_->random_system_ = muptr<RandomSystem>(*this);
    }

    if (init_system_options.init_file_system)
    {
        DisplayLog::debug("Initializing File System");
        p_->file_system_ = muptr<FileSystem>(*this);
    }

    if (init_system_options.init_simulation_system)
    {
        DisplayLog::debug("Initializing Simulation System");
        p_->simulation_system_ = muptr<SimulationSystem>(*this);
        p_->simulation_system_->initialize();
    }

    if (init_system_options.init_window_system)
    {
        p_->window_->create(nullptr);
        if (init_system_options.init_render_system)
        {
            p_->render_system_->setRenderTarget(p_->window_->renderTarget());
        }

        if (init_system_options.init_input_system)
        {
            p_->input_system_->setInputDriver(p_->window_->inputDriver());
        }
    }
}

void SystemProvider::init(rptr<IApp> iapp,
                          int const argc,
                          char const* const argv[])
{
    // TODO: Use argc and argv to read configuration.
    argc;
    argv;

    LogAsserter::log_assert(
        iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    p_->backend_factory_ =
        uptr<backend::BackendFactory, void (*)(haf::backend::BackendFactory*)>(
            createBackendFactory(), destroyBackendFactory);
    p_->app_ = iapp;

    InitSystemOptions init_system_options;
    init_system_options.setAllTrue();

    fastInit(init_system_options);

    SystemAccess system_access(this);
    DataWrapperCreator dwc(&system_access);
    p_->app_->onInit(dwc);
}

void SystemProvider::terminate()
{
    SystemAccess system_access(this);
    DataWrapperCreator dwc(&system_access);

    p_->app_->onFinish(dwc);
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

SharedDataSystem& SystemProvider::sharedDataSystem() noexcept
{
    return *p_->shared_data_system_;
}

const SharedDataSystem& SystemProvider::sharedDataSystem() const noexcept
{
    return *p_->shared_data_system_;
}

}  // namespace haf::sys
