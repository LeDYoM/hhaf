#include "host.hpp"

#include <lib/core/appcontext.hpp>
#include <lib/include/liblog.hpp>
#include <backend_dev/include/iwindow.hpp>
#include <lib/include/iapp.hpp>
#include <lib/scene/scenemanager.hpp>
#include <lib/system/backendfactory.hpp>
#include <lib/system/filesystem/filesystem.hpp>
#include <lib/system/inputsystem.hpp>
#include <lib/system/randomsystem.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/system/simulationsystem.hpp>
#include <lib/system/timesystem.hpp>
#include <lib/system/window.hpp>
#include <lib/system/rendersystem.hpp>
#include <lib/system/systemprovider.hpp>

#include <mtypes/include/parpar.hpp>
#include <mtypes/include/dicty.hpp>

#include <algorithm>
#include "config.hpp"

namespace lib::core
{
    struct ApplicationGroup
    {
        IApp* m_iapp{nullptr};
        uptr<AppContext> m_appContext;
    };

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
        ApplicationGroup m_appGroup;
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
        log_release_info("LIB version: ", LIB_VERSION_MAJOR,".", LIB_VERSION_MINOR,".", LIB_VERSION_PATCH);
        log_release_info("Parsing parameters...");
        m_private->parseCommandLineParameters();
    }

    Host::~Host() = default;

    bool Host::setApplication(IApp* iapp)
    {
        if (!m_private->m_appGroup.m_iapp && iapp) 
        {
            log_debug_info("StartingRegistering app...");
            m_private->m_appGroup.m_iapp = iapp;
            log_debug_info("Starting new app...");
            m_state = AppState::ReadyToStart;
            return true;
        }
        return false;
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

            m_private->system_provider_.init(m_private->m_appGroup.m_iapp);

            m_private->m_appGroup.m_appContext = muptr<AppContext>();
            m_private->m_appGroup.m_iapp->setSystemProvider(&(m_private->system_provider_));
            m_private->m_appGroup.m_iapp->setAppContext(&(*(m_private->m_appGroup.m_appContext)));

            m_private->m_appGroup.m_iapp->onInit();
            log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep()) 
            {
                m_state = AppState::ReadyToTerminate;
                log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": ", " is now ready to terminate");
            }
            else if (m_state == AppState::ReadyToTerminate) 
            {
                log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": ", " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": started termination");
            m_state = AppState::Terminated;
//            m_iapp->onFinish();
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
                m_private->m_appGroup.m_appContext.reset();
                m_private->m_appGroup.m_iapp;
                exit = true;
            }
        }

        if (!m_private->m_appGroup.m_iapp) 
        {
            log_release_info("App destroyed. Exiting normally");
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
