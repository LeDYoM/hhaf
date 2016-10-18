#include "host.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include <lib/draw/scenemanager.hpp>
#include <lib/draw/scene.hpp>
#include "log.hpp"
#include "eventmanager.hpp"
#include <SFML/Config.hpp>

namespace lib
{
	namespace core
	{
		std::vector<std::string> transformParams(int argc, char *argv[])
		{
			std::vector<std::string> temp;

			for (int i = 1; i<argc; ++i)
			{
				temp.push_back(argv[i]);
			}
			return temp;
		}

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
				return true;
			}
			return false;
		}

		bool Host::destroyHost() noexcept
		{
			if (m_instance) {
				delete m_instance;
				m_instance = nullptr;
				return true;
			}
			return false;
		}

		Host::Host(int argc, char *argv[])
			: m_state{ AppState::NotInitialized }
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
			LOG_INFO("Using SFML version " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << " as backend");
			LOG_INFO("Parsing parameters...");
			m_params = std::move(transformParams(argc, argv));
		}

		Host::~Host()
		{
			LOG_DESTRUCT("Name: " << appId());
		}

		bool Host::setApplication(uptr<IApp> iapp)
		{
			if (!m_iapp && iapp) {
				std::swap(m_iapp, iapp);
				LOG_DEBUG("Starting app " << appId() << "...");
				m_state = AppState::ReadyToStart;
				return true;
			}
			return false;
		}

		bool Host::update()
		{
			switch (m_state)
			{
			case lib::core::Host::AppState::NotInitialized:
				break;
			case lib::core::Host::AppState::ReadyToStart:
			{
				// Create the scene manager
				LOG_DEBUG(appId() << ": " << " Starting initialization...");
				m_state = AppState::Executing;

				//TO DO: Ask via requests
				m_eventManager = uptr<EventManager>(new EventManager());
				m_window = uptr<Window>(new Window(m_iapp->getAppDescriptor().wcp));
				m_resourceManager = uptr<ResourceManager>(new core::ResourceManager(m_iapp->getAppDescriptor().resourceFile));
				m_sceneManager = uptr<scn::SceneManager>(new scn::SceneManager());
				m_sceneManager->addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				LOG_DEBUG(appId() << ": " << " is now executing");
			}
				break;
			case lib::core::Host::AppState::Executing:
			{
				if (loopStep()) {
					m_state = AppState::ReadyToTerminate;
					LOG_DEBUG(appId() << ": " << " is now ready to terminate");
				}
			}
				break;
			case lib::core::Host::AppState::ReadyToTerminate:
				LOG_DEBUG(appId() << ": " << " started termination");
				m_state = AppState::Terminated;
//				m_iapp->onFinish();
				m_window = nullptr;
				m_sceneManager = nullptr;
				m_resourceManager = nullptr;
				m_eventManager = nullptr;
				LOG_DEBUG(appId() << ": " << " terminated");
				return true;
				break;
			case lib::core::Host::AppState::Terminated:
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
				bool terminated{ update() };
				if (terminated) {
					m_iapp.reset();
					exit = true;
				}
			}

			if (!m_iapp) {
				LOG_INFO("App destroyed. Exiting normally");
			}
			return 0;
		}

		bool Host::loopStep()
		{
			bool windowWants2Close = m_window->preLoop();
			m_eventManager->update();
			m_sceneManager->update();
			windowWants2Close |= m_window->postLoop();
			return windowWants2Close;
		}

		const std::string Host::appId() const
		{
			using std::string;
			using std::to_string;

			if (m_iapp) {
				return string(
					m_iapp->getAppDescriptor().Name + ":" + 
					to_string(m_iapp->getAppDescriptor().Version) + "." + 
					to_string(m_iapp->getAppDescriptor().SubVersion) + "." + 
					to_string(m_iapp->getAppDescriptor().Patch));
			}
			return "NoApp:0.0.0";
		}

	}
}
