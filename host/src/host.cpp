#include <host/include/host.hpp>

#include <exception>
#include <hlog/include/hlog.hpp>
#include <hosted_app/include/iapp.hpp>
#include <haf/system/include/icontrollablesystemprovider.hpp>
#include <haf/system/include/systemprovider_init.hpp>

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
    HostPrivate(const int argc, char* argv[]) :
        m_params{parpar::create(argc, argv)},
        // Hardcoded default configuration
        // TODO
        m_configuration{{}}
    {}

    ~HostPrivate() = default;

    bool parseCommandLineParameters()
    {
        if (m_params.hasParameters())
        {
        }
        return true;
    }
    parpar::ParametersParser m_params;

    Dictionary<str> m_configuration;
    IApp* iapp_{nullptr};
    IControllableSystemProvider* system_provider_;
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
    m_private{muptr<HostPrivate>(argc, argv)}, m_state{AppState::NotInitialized}
{
    DisplayLog::info("Starting HostController...");
    DisplayLog::info("Host version: ", HostVersion, ".", HostSubversion, ".",
                     HostPatch);
    DisplayLog::info("Parsing parameters...");
    m_private->parseCommandLineParameters();
}

Host::~Host() = default;

bool Host::setApplication(rptr<IApp> iapp)
{
    LogAsserter::log_assert(iapp != nullptr, "Received nullptr Application");
    LogAsserter::log_assert(!m_private->iapp_, "Application already set");

    if (!m_private->iapp_ && iapp)
    {
        DisplayLog::info("Starting Registering app...");
        m_private->iapp_ = iapp;
        DisplayLog::verbose("Starting new app...");
        m_state = AppState::ReadyToStart;
        return true;
    }
    return false;
}

str appDisplayNameAndVersion(const IApp& app)
{
    return make_str(app.getName(), "(", app.getVersion(), ".",
                    app.getSubVersion(), ".", app.getPatch(), ")");
}

bool Host::update()
{
    switch (m_state)
    {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            DisplayLog::info("Starting initialization of new App...");
            m_state = AppState::Executing;

            m_private->system_provider_ = createSystemProvider();
            m_private->system_provider_->init(m_private->iapp_);

            DisplayLog::info(appDisplayNameAndVersion(*(m_private->iapp_)),
                             ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep())
            {
                m_state = AppState::ReadyToTerminate;
                DisplayLog::info(appDisplayNameAndVersion(*(m_private->iapp_)),
                                 ": ", " is now ready to terminate");
            }
            else if (m_state == AppState::ReadyToTerminate)
            {
                DisplayLog::info(appDisplayNameAndVersion(*(m_private->iapp_)),
                                 ": ", " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            DisplayLog::info(appDisplayNameAndVersion(*(m_private->iapp_)),
                             ": started termination");
            m_state = AppState::Terminated;
            m_private->system_provider_->terminate();
            destroySystemProvider(m_private->system_provider_);
            m_private->system_provider_ = nullptr;
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
    return m_private->system_provider_->runStep();
}

void Host::exitProgram()
{
    LogAsserter::log_assert(
        m_state == AppState::Executing,
        "Cannot terminate a program that is not in the executing state");
    m_state = AppState::ReadyToTerminate;
}
}  // namespace haf::sys
