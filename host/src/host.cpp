#include <host/include/host.hpp>

#include <exception>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>
#include <haf/system/include/isystemcontroller.hpp>
#include <haf/system/include/systemprovider_init.hpp>
#include <loader/include/loader.hpp>
#include <mtypes/include/parpar.hpp>
#include <mtypes/include/object.hpp>

using namespace mtps;

namespace
{
constexpr static const char HostVersion[]    = "1";
constexpr static const char HostSubversion[] = "2";
constexpr static const char HostPatch[]      = "0";
}  // namespace

namespace haf::sys
{
class Host::HostPrivate final
{
public:
    HostPrivate(const int argc, char const* const argv[]) :
        argc_{argc},
        argv_{argv},
        params_{parpar::create(argc, argv)},
        // Hardcoded default configuration
        // TODO
        configuration_{{}}
    {}

    ~HostPrivate() = default;

    bool parseCommandLineParameters()
    {
        if (params_.hasParameters())
        {
        }
        return true;
    }
    parpar::ParametersParser params_;

    Dictionary<str> configuration_;
    rptr<IApp> iapp_{nullptr};
    rptr<ISystemController> system_controller_{nullptr};

    int const argc_;
    char const* const* const argv_;
    rptr<loader::Loader> loader_{nullptr};
};

enum class Host::AppState : u8
{
    NotInitialized,
    ReadyToStart,
    Executing,
    ReadyToTerminate,
    Terminated
};

Host::Host(int argc, char* argv[]) :
    p_{muptr<HostPrivate>(argc, argv)}, app_state_{AppState::NotInitialized}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", HostVersion, ".", HostSubversion, ".",
                     HostPatch);
    DisplayLog::info("Parsing parameters...");
    p_->parseCommandLineParameters();
}

Host::~Host() = default;

bool Host::setApplication(rptr<IApp> iapp)
{
    LogAsserter::log_assert(iapp != nullptr, "Received nullptr Application");
    LogAsserter::log_assert(!p_->iapp_, "Application already set");

    if (!p_->iapp_ && iapp)
    {
        DisplayLog::info("Starting Registering app...");
        p_->iapp_ = iapp;
        DisplayLog::verbose("Starting new app...");
        app_state_ = AppState::ReadyToStart;
        return true;
    }
    return false;
}

str appDisplayNameAndVersion(const IApp& app)
{
    return make_str(app.getName(), "(", app.getVersion(), ".",
                    app.getSubVersion(), ".", app.getPatch(), ")");
}

using CreateSystemController_t = ISystemController* (*)createSystemController();

bool Host::update()
{
    switch (app_state_)
    {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            DisplayLog::info("Starting initialization of new App...");
            app_state_ = AppState::Executing;

            p_->loader_ = loader::createLoader();

            constexpr const char haf_library[] = "haf";
            if (loader->loadModule(haf_library))
            {
                const auto fp_p_haf_create_system_controller = static_cast<p_haf_host_main>(
                    loader->loadMethod(host_library, "haf_host_main"));

                if (fp_p_haf_host_main != nullptr)
                {
                    // The haf_host_main method was loaded successfully.
                    // Call it.
                    result = (*fp_p_haf_host_main)(argc, argv);
                }
                else
                {
                    result = -1;
                }
            }

            p_->system_controller_ = createSystemController();
            p_->system_controller_->init(p_->iapp_);

            DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)),
                             ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                app_state_ = AppState::ReadyToTerminate;
                DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)), ": ",
                                 " is now ready to terminate");
            }
            else if (app_state_ == AppState::ReadyToTerminate)
            {
                DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)), ": ",
                                 " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*(p_->iapp_)),
                             ": started termination");
            app_state_ = AppState::Terminated;
            p_->system_controller_->terminate();
            destroySystemController(p_->system_controller_);
            p_->system_controller_ = nullptr;
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

int Host::run()
{
    try
    {
        while (!exit)
        {
            if (update())
            {
                exit = true;
            }
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        DisplayLog::error(e.what());
    }
    return 1;
}

bool Host::loopStep()
{
    return p_->system_controller_->runStep();
}

void Host::exitProgram()
{
    LogAsserter::log_assert(
        app_state_ == AppState::Executing,
        "Cannot terminate a program that is not in the executing state");
    app_state_ = AppState::ReadyToTerminate;
}
}  // namespace haf::sys
