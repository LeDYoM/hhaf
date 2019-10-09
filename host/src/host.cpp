#include <host/include/host.hpp>

#include <lib/include/liblog.hpp>
#include <lib/include/iapp.hpp>
#include <lib/system/systemprovider.hpp>

#include <mtypes/include/parpar.hpp>
#include <mtypes/include/object.hpp>

namespace
{
    constexpr static const char HostVersion[] = "1";
    constexpr static const char HostSubversion[] = "1";
    constexpr static const char HostPatch[] = "0";
}

namespace lib::core
{
    class Host::HostPrivate final
    {
    public:
        HostPrivate(const int argc, char *argv[]) :
            m_params{parpar::create(argc,argv)},
            // Hardcoded default configuration
            // TODO
            m_configuration{
                {}
            }
        { }

        ~HostPrivate() = default;

        bool parseCommandLineParameters()
        {
            if (m_params.hasParameters()) {

            }
            return true;
        }
        parpar::ParametersParser m_params;

        Dictionary<str> m_configuration;
        IApp* iapp_{nullptr};
        SystemProvider system_provider_;
    };

    enum class Host::AppState : u8
    {
        NotInitialized,
        ReadyToStart,
        Executing,
        ReadyToTerminate,
        Terminated
    };

    Host::Host(int argc, char *argv[])
        : m_private{muptr<HostPrivate>(argc,argv)}, m_state{ AppState::NotInitialized }
    {
        log_release_info("Starting HostController...");
        log_release_info("Host version: ", HostVersion,".", HostSubversion,".", HostPatch);
        log_release_info("Parsing parameters...");
        m_private->parseCommandLineParameters();
    }

    Host::~Host() = default;

    bool Host::setApplication(IApp* iapp)
    {
        if (!m_private->iapp_ && iapp) 
        {
            log_debug_info("StartingRegistering app...");
            m_private->iapp_ = iapp;
            log_debug_info("Starting new app...");
            m_state = AppState::ReadyToStart;
            return true;
        }
        return false;
    }

    inline str appDisplayNameAndVersion(const IApp& app) noexcept
    {
        return make_str(app.getName(), "(", app.getVersion(), ".", app.getSubVersion(), ".", app.getPatch(), ")");
    }

    bool Host::update()
    {
        switch (m_state)
        {
        case AppState::NotInitialized:
            break;
        case AppState::ReadyToStart:
        {
            log_debug_info("Starting initialization of new App...");
            m_state = AppState::Executing;

            m_private->system_provider_.init(m_private->iapp_);
            m_private->iapp_->setSystemProvider(&(m_private->system_provider_));

            m_private->iapp_->onInit();
            log_debug_info(appDisplayNameAndVersion(*(m_private->iapp_)),
                ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep()) 
            {
                m_state = AppState::ReadyToTerminate;
                log_debug_info(appDisplayNameAndVersion(*(m_private->iapp_)), ": ", " is now ready to terminate");
            }
            else if (m_state == AppState::ReadyToTerminate) 
            {
                log_debug_info(appDisplayNameAndVersion(*(m_private->iapp_)), ": ", " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            log_debug_info(appDisplayNameAndVersion(*(m_private->iapp_)), ": started termination");
            m_state = AppState::Terminated;
            m_private->iapp_->onFinish();
            m_private->system_provider_.terminate();
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
        while (!exit) 
        {
            if (update()) 
            {
                exit = true;
            }
        }

        return 0;
    }

    bool Host::loopStep()
    {
        return m_private->system_provider_.runStep();
    }

    void Host::exitProgram()
    {
        assert_release(m_state == AppState::Executing, "Cannot terminate a program that is not in the executing state");
        m_state = AppState::ReadyToTerminate;
    }
}
