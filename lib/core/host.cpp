#include "host.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "randomizer.hpp"

#include <lib/scene/scenemanager.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/backend/backendfactory.hpp>
#include <lib/backend/iwindow.hpp>
#include <lib/core/debugsystem.hpp>

#include <mtypes/include/log.hpp>
#include <mtypes/include/parpar.hpp>
#include <mtypes/include/dicty.hpp>

#include <algorithm>

#define LIB_VERSION_MAJOR 1
#define LIB_VERSION_MINOR 4
#define LIB_VERSION_PATCH 2

#define ACCEPT_PARAMETERS

namespace lib::core
{
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
        BasicDictionary m_configuration;
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
        logConstruct_NOPARAMS;
        log_release_info("Starting HostController...");
        log_release_info("LIB version: ", LIB_VERSION_MAJOR,".", LIB_VERSION_MINOR,".", LIB_VERSION_PATCH);
#ifdef ACCEPT_PARAMETERS
        log_release_info("Parsing parameters...");
        m_private->parseCommandLineParameters();
#endif
    }

    Host::~Host()
    {
        logDestruct_NOPARAMS;
    }

    bool Host::setApplication(uptr<IApp> iapp)
    {
        if (!m_iapp && iapp) {
            m_iapp = std::move(iapp);
            log_debug_info("Starting app ", appId(), "...");
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
            log_debug_info(appId(), ": Starting initialization...");
            m_state = AppState::Executing;

            m_inputSystem = muptr<input::InputSystem>();
            m_randomizer = muptr<Randomizer>();
            m_window = muptr<Window>(m_iapp->getAppDescriptor().wcp);
            m_sceneManager = muptr<scene::SceneManager>(*m_window);
            m_resourceManager = muptr<core::ResourceManager>();
            m_debugSystem = muptr<DebugSystem>();

            m_iapp->onInit();
            log_debug_info(appId(), ": Starting execution...");
        }
        break;
        case AppState::Executing:
        {
            if (loopStep()) {
                m_state = AppState::ReadyToTerminate;
                log_debug_info(appId(), ": ", " is now ready to terminate");
            }
            else if (m_state == AppState::ReadyToTerminate) {
                log_debug_info(appId(), ": ", " requested to terminate");
            }
        }
        break;
        case AppState::ReadyToTerminate:
            log_debug_info(appId(), ": started termination");
            m_sceneManager->finish();
            m_state = AppState::Terminated;
//				m_iapp->onFinish();
            m_debugSystem = nullptr;
            m_sceneManager = nullptr;
            m_window = nullptr;
            m_resourceManager = nullptr;
            m_randomizer = nullptr;
            m_inputSystem = nullptr;
            m_private = nullptr;
            log_debug_info(appId(), ": terminated");
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
                m_iapp.reset();
                exit = true;
            }
        }

        if (!m_iapp) {
            log_release_info("App destroyed. Exiting normally");
        }
        return 0;
    }

    bool Host::loopStep()
    {
        const bool windowWants2Close{ m_window->preLoop() };
        m_inputSystem->preUpdate();
        m_sceneManager->update();

        __ASSERT(m_currentScene || m_nextScene, "Current scene and nextscene cannot be nullptr at same time");

        m_window->postLoop();
        m_inputSystem->postUpdate();
        return windowWants2Close;
    }

    void Host::exitProgram()
    {
        __ASSERT(m_state == AppState::Executing, "Cannot terminate a program that is not in the executing state");
        m_state = AppState::ReadyToTerminate;
    }

    const str Host::appId() const
    {
        if (m_iapp) {
            const auto &cAppDescriptor(m_iapp->getAppDescriptor());
            return make_str(cAppDescriptor.Name, ":", cAppDescriptor.Version, ".", cAppDescriptor.SubVersion, ".", cAppDescriptor.Patch);
        }
        return "NoApp:0.0.0";
    }
}
