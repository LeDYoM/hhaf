#include "host.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "randomsystem.hpp"

#include <lib/include/backend/iwindow.hpp>
#include <lib/include/core/log.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/core/backendfactory.hpp>
#include <lib/core/appcontext.hpp>
#include <lib/core/hostcontext.hpp>
#include <lib/scene/scenemanager.hpp>

#include <mtypes/include/parpar.hpp>
#include <mtypes/include/dicty.hpp>

#include <algorithm>
#include "config.hpp"

#define ACCEPT_PARAMETERS

namespace lib::core
{
    struct ApplicationGroup
    {
        uptr<IApp> m_iapp;
        uptr<HostContext> m_hostContext;
        uptr<AppContext> m_appContext;
    };

    class HostPrivate final
    {
    public:
        HostPrivate(const int argc, char *argv[]) :
#ifdef ACCEPT_PARAMETERS
            m_params{parpar::create(argc,argv)},
#endif
            // Hardcoded default configuration
            // TODO
            m_configuration{
                {}
            }
        {

        }

#ifdef ACCEPT_PARAMETERS
        bool parseCommandLineParameters()
        {
            if (m_params.hasParameters()) {

            }
            return true;
        }
        parpar::ParametersParser m_params;
#endif

        dicty::BasicDictionary<str> m_configuration;

        ApplicationGroup m_appGroup;
    };

    enum class Host::AppState : u8
    {
        NotInitialized,
        ReadyToStart,
        Executing,
        ReadyToTerminate,
        Terminated
    };

    Host *Host::m_instance = nullptr;

    bool Host::createHost(int argc, char * argv[])
    {
        if (!m_instance) {
            m_instance = new Host(argc, argv);
            backend::BackendFactory::initilialize("bsfml");
            return true;
        }
        return false;
    }

    bool Host::destroyHost() noexcept
    {
        if (m_instance) {
            backend::BackendFactory::destroy();
            delete m_instance;
            m_instance = nullptr;
            return true;
        }
        return false;
    }

    Host::Host(int argc, char *argv[])
        : m_private{muptr<HostPrivate>(argc,argv)}, m_state{ AppState::NotInitialized }
    {
        log_release_info("Starting HostController...");
        log_release_info("LIB version: ", LIB_VERSION_MAJOR,".", LIB_VERSION_MINOR,".", LIB_VERSION_PATCH);
#ifdef ACCEPT_PARAMETERS
        log_release_info("Parsing parameters...");
        m_private->parseCommandLineParameters();
#endif
    }

    Host::~Host() = default;

    bool Host::setApplication(uptr<IApp> iapp)
    {
        if (!m_private->m_appGroup.m_iapp && iapp) 
        {
            log_debug_info("StartingRegistering app...");
            m_private->m_appGroup.m_iapp = std::move(iapp);
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

            SystemProvider::init(*this, m_private->m_appGroup.m_iapp->getAppDescriptor().wcp);

            m_private->m_appGroup.m_hostContext = muptr<HostContext>(this);
            m_private->m_appGroup.m_appContext = muptr<AppContext>(this);
            m_private->m_appGroup.m_iapp->setHostContext(&(*(m_private->m_appGroup.m_hostContext)));
            m_private->m_appGroup.m_iapp->setAppContext(&(*(m_private->m_appGroup.m_appContext)));

            m_private->m_appGroup.m_iapp->onInit();
            log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep()) {
                m_state = AppState::ReadyToTerminate;
                log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": ", " is now ready to terminate");
            }
            else if (m_state == AppState::ReadyToTerminate) {
                log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": ", " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            log_debug_info(m_private->m_appGroup.m_appContext->appId(), ": started termination");
            m_state = AppState::Terminated;
//				m_iapp->onFinish();
            SystemProvider::terminate();
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
        while (!exit) {
            if (update()) {
                m_private->m_appGroup.m_hostContext.reset();
                m_private->m_appGroup.m_appContext.reset();
                m_private->m_appGroup.m_iapp.reset();
                exit = true;
            }
        }

        if (!m_private->m_appGroup.m_iapp) {
            log_release_info("App destroyed. Exiting normally");
        }
        return 0;
    }

    bool Host::loopStep()
    {
        const bool windowWants2Close{ parentWindow().preLoop() };
        inputSystem().preUpdate();
        sceneManager().update();

        parentWindow().postLoop();
        inputSystem().postUpdate();
        return windowWants2Close;
    }

    void Host::exitProgram()
    {
        assert_release(m_state == AppState::Executing, "Cannot terminate a program that is not in the executing state");
        m_state = AppState::ReadyToTerminate;
    }

    IApp &Host::app()
    {
        return *(m_private->m_appGroup.m_iapp);
    }
}
