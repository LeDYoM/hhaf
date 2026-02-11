module;

#include <host_haf_interface/include/isystem_controller.hpp>
#include <hosted_app/include/iapp.hpp>

export module host:host_internal;

import :host;
import :hosted_application;
import :app_loader;
import :app_state;
import :system_controller_loader;
import :host_connector;
import :host_connector_impl;
import :host_log;

import parpar;
import backend;

namespace haf::host
{
class HostInternal
{
public:
    HostInternal(int const argc, char const* const argv[])
        HostInternal::HostInternal(const int argc, char const* const argv[]) :
        argc_{argc},
        argv_{argv},
        backend_factory_{nullptr},
        config_{argc, argv},
        params_{parpar::create(argc, argv)}
    {}

    int const argc_;
    char const* const* const argv_;
    BackendFactoryUPtr backend_factory_;

    HostConfig config_;
    parpar::ParametersParser params_;
    SystemControllerLoader system_loader_;
    AppLoader app_loader;
    HostedAppGroup app_group_;

    bool initialize()
    {
        // Parse command line arguments and process parameters
        config_.processCommandLineArguments();

        auto const result_init_backend{initializeBackend()};
        auto const result_load_functions{initializeHaf()};

        // Return the status of loading the first application
        return result_init_backend && result_load_functions &&
            loadApplication(config_.configuredFirstApp());
    }

    /**
     * @brief Performs the main update cycle, updating all current active
     * applications.
     *
     * @return true The host wants to exit
     * @return false The host wants to continue
     */
    bool update()
    {
        // By default, the host wants to exit.
        // Only the existence of at least one application that
        // does not want to exit will avoid that.
        bool all_apps_want_to_exit{true};

        if (!app_group_.empty())
        {
            const bool pre_update_wants_tp_exit{
                app_group_.front().app_system_controller->preUpdate()};

            if (!pre_update_wants_tp_exit)
            {
                for (auto& app : app_group_)
                {
                    // Any app not wanting to exit will return false,
                    // so any false will set all_apps_want_to_exit to false
                    all_apps_want_to_exit &= updateApp(app);
                }
            }

            // If the system, in the post update stage requires to exit, we
            // should exit
            all_apps_want_to_exit |=
                app_group_.front().app_system_controller->postUpdate();
        }
        return all_apps_want_to_exit;
    }

    bool addApplication(ManagedApp managed_app, htps::str name)
    {
        auto host_connector_impl = muptr<HostConnectorImpl>(*this);
        auto host_connector =
            muptr<HostConnector>(htps::move(host_connector_impl));
        return app_group_.try_add_app(htps::move(managed_app), htps::move(name),
                                      htps::move(host_connector));
    }

    bool loadApplication(htps::str const& app_name)
    {
        ManagedApp managed_app = app_loader.loadApp(app_name);
        bool const result_add{
            managed_app.app != nullptr
                ? addApplication(htps::move(managed_app), app_name)
                : false};

        if (result_add)
        {
            // Create a new system controller
            auto app_system_controller{system_loader_.create()};
            if (app_system_controller == nullptr)
            {
                // Remove the newly added app
                app_group_.pop_back();
                DisplayLog::error("Cannot create haf system!");
            }
            else
            {
                auto& app                 = app_group_.back();
                app.app_system_controller = htps::move(app_system_controller);
                app.app_system_controller->init(app.managed_app_.app, nullptr,
                                                backend_factory_.get(), argc_,
                                                argv_);

                DisplayLog::info(appDisplayNameAndVersion(app),
                                 ": Starting execution...");
                return true;
            }
        }
        return false;
    }

    bool unloadApplication(htps::str app_name)
    {
        if (app_group_.appExists(app_name))
        {
            // This is safe, given that app exists
            auto hosted_app = app_group_[app_name];
            auto& app       = hosted_app->managed_app_;
            hosted_app->app_system_controller->terminate();
            hosted_app->app_system_controller.reset();
            app_loader.unloadApp(app);
            return app_group_.removeApp(app_name);
        }
        return false;
    }

    bool unloadAllApplications()
    {
        bool result{true};

        while (!app_group_.empty())
        {
            HostedApplication& last = app_group_.back();
            result &= unloadApplication(last.app_name_);
        }
        return result;
    }

    htps::str simulation_input_file;
    htps::str simulation_output_file;
    bool exit{false};

private:
    /**
     * @brief Updates a given @b HostApplication, performing actions
     * depending on which state the application currently is.
     *
     * @param app Application to update
     * @return true The application wants to exit
     * @return false The application wants to continue executing
     */
    bool updateApp(HostedApplication& app)
    {
        switch (app.app_state)
        {
            case AppState::NotInitialized:
                break;
            case AppState::ReadyToStart:
            {
                HostLogDisplayer::info("Starting initialization of new App...");
                app.app_state = AppState::Executing;
            }
            break;
            case AppState::Executing:
            {
                if (app.app_system_controller->update())
                {
                    app.app_state = AppState::ReadyToTerminate;
                    HostLogDisplayer::info(appDisplayNameAndVersion(app),
                                           ": is now ready to terminate");
                }
            }
            break;
            case AppState::ReadyToTerminate:
                HostLogDisplayer::info(appDisplayNameAndVersion(app),
                                       ": ready to terminate");
                app.app_state = AppState::Terminated;
                return true;
                break;
            case AppState::Terminated:
                return true;
                break;
            default:
                break;
        }
        return false;
    }

    bool initializeBackend()
    {
        // Initialize and create the backend factory
        backend_factory_ =
            uptr<backend::BackendFactory>{createBackendFactory()};
        backend_factory_->loadBackendFile("bsfml");
        backend_factory_->loadBackendFile("haf_integrated_backend");
        logLoadedFactories();

        return backend_factory_ != nullptr;
    }

    void logLoadedFactories()
    {
        LogAsserter::log_assert(backend_factory_ != nullptr,
                                "No backend loaded!");
        HostLogDisplayer::debug(
            "Window loaded loaded...\t\t",
            backend_factory_->isWindowFactoryAvailable() ? "Yes" : "No");
        HostLogDisplayer::debug(
            "Texture factory loaded...\t",
            backend_factory_->getTextureFactory() ? "Yes" : "No");
        HostLogDisplayer::debug(
            "BMPFont factory loaded...\t",
            backend_factory_->isBMPFontFactoryAvailable() ? "Yes" : "No");
        HostLogDisplayer::debug(
            "TTFont factory loaded...\t\t",
            backend_factory_->isTTFontFactoryAvailable() ? "Yes" : "No");
        HostLogDisplayer::debug(
            "Shader factory loaded...\t\t",
            backend_factory_->isShaderFactoryAvailable() ? "Yes" : "No");
    }

    bool initializeHaf()
    {
        auto const result_load_functions{system_loader_.loadFunctions()};
        HostLogDisplayer::error_if(
            result_load_functions !=
                SystemControllerLoader::ResultType::Success,
            "Cannot load haf system!");

        return result_load_functions ==
            SystemControllerLoader::ResultType::Success;
    }
};

}  // namespace haf::host
