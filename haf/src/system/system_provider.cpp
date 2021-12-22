#include "system_provider.hpp"
#include "system_provider_configuration.hpp"
#include "init_system_options.hpp"

#include <backend/include/backendfactory.hpp>
#include <backend/include/backend_creator.hpp>
#include "debug_utils/debug_system.hpp"
#include "filesystem/file_system.hpp"
#include "input/inputsystem.hpp"
#include "random/randomsystem.hpp"
#include "render/rendersystem.hpp"
#include "scene/scene_manager.hpp"
#include "window/window.hpp"
#include "time/time_system.hpp"
#include "shareddata/shared_data_system.hpp"
#include "resources/resource_manager.hpp"
#include "simulation/simulation_system.hpp"

#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

#include <haf/include/system/system_access.hpp>
#include <haf/include/scene_components/iapp_initializer.hpp>
#include <haf/include/scene_components/iapp_finisher.hpp>

#include <htypes/include/parpar.hpp>

using namespace htps;

namespace haf::sys
{
struct SystemProvider::SystemProviderPrivate final
{
    rptr<IApp> app_{nullptr};
    uptr<DebugSystem> debug_system_;
    uptr<SharedDataSystem> shared_data_system_;
    BackendFactoryPtr backend_factory_{nullptr};
    uptr<Window> window_;
    uptr<ResourceManager> resource_manager_;
    uptr<InputSystem> input_system_;
    uptr<scene::SceneManager> scene_manager_;
    uptr<RandomSystem> random_system_;
    uptr<FileSystem> file_system_;
    uptr<TimeSystem> time_system_;
    uptr<RenderSystem> render_system_;
    uptr<SimulationSystem> simulation_system_;

    str haf_configuration_file_;
    SystemProviderConfiguration system_provdier_configuration_;

    void setArgumments(parpar::ParametersParser parameter_parser)
    {
        if (parameter_parser.hasParameters())
        {
            static constexpr char kHafConfigurationFileParameter[] =
                "haf_config";

            auto const haf_configuration_file_value{
                parameter_parser.optionValue(kHafConfigurationFileParameter)};

            if (haf_configuration_file_value.first)
            {
                haf_configuration_file_ = haf_configuration_file_value.second;
                DisplayLog::debug(
                    "Parameter ", kHafConfigurationFileParameter,
                    " found with value: ", haf_configuration_file_);
            }
        }
    }

    void loadConfiguration(SubSystemViewer sub_system_viewer)
    {
        if (!haf_configuration_file_.empty())
        {
            system_provdier_configuration_.loadConfiguration(
                std::move(sub_system_viewer), haf_configuration_file_);
        }
    }
};

SystemProvider::SystemProvider() : p_{make_pimplp<SystemProviderPrivate>()}
{}

SystemProvider::~SystemProvider() = default;

namespace
{
template <typename T>
void configureSystem(T& system, str const& file_name)
{
    const auto& configuration_file{file_name};

    if (!configuration_file.empty())
    {
        DisplayLog::debug("Using configuration file: ", configuration_file);
    }

    system->initialize(configuration_file);
}

}  // namespace

void SystemProvider::createSystems(InitSystemOptions const& init_system_options)
{
    instanciateSystems(init_system_options);
    p_->loadConfiguration(SubSystemViewer(this));
    initializeSystems(init_system_options);
}

void SystemProvider::instanciateSystems(
    InitSystemOptions const& init_system_options)
{
    if (init_system_options.init_file_system)
    {
        DisplayLog::debug("Initializing File System");
        p_->file_system_ = muptr<FileSystem>(*this);
    }

    if (init_system_options.init_debug_system)
    {
        DisplayLog::debug("Initializing DebugSystem");
        p_->debug_system_ = muptr<DebugSystem>(*this);
    }

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

    if (init_system_options.init_simulation_system)
    {
        DisplayLog::debug("Initializing Simulation System");
        p_->simulation_system_ = muptr<SimulationSystem>(*this);
    }
}

void SystemProvider::initializeSystems(
    InitSystemOptions const& init_system_options)
{
    if (init_system_options.init_simulation_system)
    {
        configureSystem(p_->simulation_system_,
                        p_->system_provdier_configuration_
                            .simulationSystemConfigurationFile());
    }

    if (init_system_options.init_window_system)
    {
        DisplayLog::debug("Initializing Window");

        configureSystem(
            p_->window_,
            p_->system_provdier_configuration_.windowSystemConfigurationFile());

        if (init_system_options.init_render_system)
        {
            p_->render_system_->setRenderTarget(p_->window_->renderTarget());
        }

        if (init_system_options.init_input_system)
        {
            p_->input_system_->setInputDriverWrapper(
                p_->window_->inputDriverWrapper());
        }
    }
}

void SystemProvider::setBackend(
    htps::rptr<backend::BackendFactory> backend_factory)
{
    LogAsserter::log_assert(backend_factory != nullptr,
                            "nullptr backend_factory received");
    LogAsserter::log_assert(p_->backend_factory_ == nullptr,
                            "backend_factory_ was already initialized");
    p_->backend_factory_ = backend_factory;
}

void SystemProvider::init(rptr<IApp> iapp,
                          rptr<backend::BackendFactory> backend_factory,
                          int const argc,
                          char const* const argv[])
{
    parpar::ParametersParser parameter_parser{parpar::create(argc, argv)};
    p_->setArgumments(parameter_parser);

    LogAsserter::log_assert(
        backend_factory != nullptr,
        "Cannot create a SystemProvider with a nullptr backend_factory");

    LogAsserter::log_assert(
        iapp != nullptr, "Cannot create a SystemProvider with a nullptr app");
    setBackend(backend_factory);
    p_->app_ = iapp;

    InitSystemOptions init_system_options;
    init_system_options.setAllTrue();

    createSystems(init_system_options);

    p_->app_->onInit(
        *(SubSystemViewer{this}.subSystem<scene::IAppInitializer>()));
}

void SystemProvider::terminate()
{
    p_->app_->onFinish(
        *(SubSystemViewer{this}.subSystem<scene::IAppFinisher>()));
    p_->scene_manager_->finish();
    p_->scene_manager_.reset();
    p_->simulation_system_.reset();
    p_->random_system_.reset();
    p_->render_system_.reset();
    p_->resource_manager_.reset();
    p_->scene_manager_.reset();
    p_->input_system_.reset();
    p_->window_.reset();
    p_->time_system_.reset();
    p_->debug_system_.reset();
    p_->file_system_.reset();
    p_->backend_factory_ = nullptr;
}

IApp& SystemProvider::app()
{
    return *p_->app_;
}

IApp const& SystemProvider::app() const
{
    return *p_->app_;
}

Window const& SystemProvider::window() const noexcept
{
    return *p_->window_;
}

Window& SystemProvider::window() noexcept
{
    return *p_->window_;
}

ResourceManager const& SystemProvider::resourceManager() const noexcept
{
    return *p_->resource_manager_;
}

ResourceManager& SystemProvider::resourceManager() noexcept
{
    return *p_->resource_manager_;
}

InputSystem const& SystemProvider::inputSystem() const noexcept
{
    return *p_->input_system_;
}

InputSystem& SystemProvider::inputSystem() noexcept
{
    return *p_->input_system_;
}

RandomSystem const& SystemProvider::randomSystem() const noexcept
{
    return *p_->random_system_;
}

RandomSystem& SystemProvider::randomSystem() noexcept
{
    return *p_->random_system_;
}

FileSystem const& SystemProvider::fileSystem() const noexcept
{
    return *p_->file_system_;
}

FileSystem& SystemProvider::fileSystem() noexcept
{
    return *p_->file_system_;
}

scene::SceneManager const& SystemProvider::sceneManager() const noexcept
{
    return *p_->scene_manager_;
}

scene::SceneManager& SystemProvider::sceneManager() noexcept
{
    return *p_->scene_manager_;
}

SimulationSystem const& SystemProvider::simulationSystem() const noexcept
{
    return *p_->simulation_system_;
}

SimulationSystem& SystemProvider::simulationSystem() noexcept
{
    return *p_->simulation_system_;
}

TimeSystem const& SystemProvider::timeSystem() const noexcept
{
    return *p_->time_system_;
}

TimeSystem& SystemProvider::timeSystem() noexcept
{
    return *p_->time_system_;
}

backend::BackendFactory const& SystemProvider::backendFactory() const noexcept
{
    return *p_->backend_factory_;
}

backend::BackendFactory& SystemProvider::backendFactory() noexcept
{
    return *p_->backend_factory_;
}

RenderSystem const& SystemProvider::renderSystem() const noexcept
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

SharedDataSystem const& SystemProvider::sharedDataSystem() const noexcept
{
    return *p_->shared_data_system_;
}

DebugSystem const& SystemProvider::debugSystem() const noexcept
{
    return *p_->debug_system_;
}

DebugSystem& SystemProvider::debugSystem() noexcept
{
    return *p_->debug_system_;
}

template <>
SharedDataSystem const& SystemProvider::system() const noexcept
{
    return sharedDataSystem();
}

template <>
SharedDataSystem& SystemProvider::system() noexcept
{
    return sharedDataSystem();
}

template <>
TimeSystem const& SystemProvider::system() const noexcept
{
    return timeSystem();
}

template <>
TimeSystem& SystemProvider::system() noexcept
{
    return timeSystem();
}

template <>
scene::SceneManager const& SystemProvider::system() const noexcept
{
    return sceneManager();
}

template <>
scene::SceneManager& SystemProvider::system() noexcept
{
    return sceneManager();
}

template <>
Window const& SystemProvider::system() const noexcept
{
    return window();
}

template <>
Window& SystemProvider::system() noexcept
{
    return window();
}

template <>
ResourceManager const& SystemProvider::system() const noexcept
{
    return resourceManager();
}

template <>
ResourceManager& SystemProvider::system() noexcept
{
    return resourceManager();
}

template <>
InputSystem const& SystemProvider::system() const noexcept
{
    return inputSystem();
}

template <>
InputSystem& SystemProvider::system() noexcept
{
    return inputSystem();
}

template <>
RandomSystem const& SystemProvider::system() const noexcept
{
    return randomSystem();
}

template <>
RandomSystem& SystemProvider::system() noexcept
{
    return randomSystem();
}

template <>
FileSystem const& SystemProvider::system() const noexcept
{
    return fileSystem();
}

template <>
FileSystem& SystemProvider::system() noexcept
{
    return fileSystem();
}

template <>
RenderSystem const& SystemProvider::system() const noexcept
{
    return renderSystem();
}

template <>
RenderSystem& SystemProvider::system() noexcept
{
    return renderSystem();
}

template <>
SimulationSystem const& SystemProvider::system() const noexcept
{
    return simulationSystem();
}

template <>
SimulationSystem& SystemProvider::system() noexcept
{
    return simulationSystem();
}

template <>
DebugSystem const& SystemProvider::system() const noexcept
{
    return debugSystem();
}

template <>
DebugSystem& SystemProvider::system() noexcept
{
    return debugSystem();
}

}  // namespace haf::sys
