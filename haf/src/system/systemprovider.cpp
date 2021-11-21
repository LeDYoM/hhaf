#include "systemprovider.hpp"
#include "system_provider_configuration.hpp"
#include "init_system_options.hpp"

#include <backend/include/backendfactory.hpp>
#include <backend/include/backend_creator.hpp>
#include "debug_utils/debug_system.hpp"
#include "filesystem/filesystem.hpp"
#include "input/inputsystem.hpp"
#include "random/randomsystem.hpp"
#include "render/rendersystem.hpp"
#include "scene/scenemanager.hpp"
#include "window/window.hpp"
#include "time/timesystem.hpp"
#include "shareddata/shareddatasystem.hpp"
#include "resources/resourcemanager.hpp"
#include "simulation/simulation_system.hpp"

#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>

#include <haf/include/system/datawrappercreator.hpp>
#include <haf/include/system/systemaccess.hpp>
#include <haf/include/scene_components/app_initializer.hpp>
#include <haf/include/scene_components/app_finisher.hpp>

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
    str simulation_config_file_;
    SystemProviderConfiguration system_provdier_configuration_;

    void setArgumments(parpar::ParametersParser parameter_parser)
    {
        if (parameter_parser.hasParameters())
        {
            static constexpr char kHafConfigurationFileParameter[] = "haf_config";

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

    void loadConfiguration(SystemProvider&)
    {
        if (!haf_configuration_file_.empty())
        {
//            system_provdier_configuration_.loadConfiguration(
//                haf_configuration_file_);
        }
    }
};

SystemProvider::SystemProvider() : p_{muptr<SystemProviderPrivate>()}
{}

SystemProvider::~SystemProvider() = default;

void SystemProvider::fastInit(InitSystemOptions const& init_system_options)
{
    if (init_system_options.init_debug_system)
    {
        DisplayLog::debug("Initializing DebugSystem");
        p_->shared_data_system_ = muptr<SharedDataSystem>(*this);
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

    if (init_system_options.init_file_system)
    {
        DisplayLog::debug("Initializing File System");
        p_->file_system_ = muptr<FileSystem>(*this);
    }

    if (init_system_options.init_simulation_system)
    {
        DisplayLog::debug("Initializing Simulation System");
        p_->simulation_system_ = muptr<SimulationSystem>(*this);
        if (!p_->simulation_config_file_.empty())
        {
            DisplayLog::debug(
                "Passing simulation config file to simulation system: ",
                p_->simulation_config_file_);
        }

//        p_->simulation_system_->initialize(p_->simulation_config_file_);
        p_->simulation_system_->initialize("simulation_configuration.txt");
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
            p_->input_system_->setInputDriverWrapper(
                p_->window_->inputDriverWrapper());
        }
    }
}

void SystemProvider::createBackend()
{
    //    p_->backend_factory_ =
    //        uptr<backend::BackendFactory, void
    //        (*)(haf::backend::BackendFactory*)>(
    //            createBackendFactory(), destroyBackendFactory);
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

    fastInit(init_system_options);

    SystemAccess system_access(this);
    DataWrapperCreator dwc(&system_access);
    p_->app_->onInit(*dwc.dataWrapper<scene::AppInitializer>());
}

void SystemProvider::terminate()
{
    SystemAccess system_access(this);
    DataWrapperCreator dwc(&system_access);

    p_->app_->onFinish(*dwc.dataWrapper<scene::AppFinisher>());
    p_->scene_manager_->finish();
    p_->scene_manager_.reset();
    p_->simulation_system_.reset();
    p_->file_system_.reset();
    p_->random_system_.reset();
    p_->render_system_.reset();
    p_->resource_manager_.reset();
    p_->scene_manager_.reset();
    p_->input_system_.reset();
    p_->window_.reset();
    p_->time_system_.reset();
    p_->debug_system_.reset();
    p_->backend_factory_ = nullptr;
}

IApp& SystemProvider::app()
{
    return *p_->app_;
}

const IApp& SystemProvider::app() const
{
    return *p_->app_;
}

const Window& SystemProvider::window() const noexcept
{
    return *p_->window_;
}

Window& SystemProvider::window() noexcept
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

const DebugSystem& SystemProvider::debugSystem() const noexcept
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
