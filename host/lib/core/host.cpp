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

		Host::Host(int argc, char *argv[])
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
			if (!m_iapp && iapp)
			{
				std::swap(m_iapp, iapp);
				LOG_DEBUG("Starting app " << appId() << "...");
				m_state = AppState::ReadyToStart;
				return true;
			}
			return false;
		}

		bool Host::update()
		{
			bool _continue{ true };

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
				m_eventManager = uptr<EventManager>(new EventManager(this));
				m_window = uptr<Window>(new Window(this, m_iapp->getAppDescriptor().wcp));
				m_resourceManager = uptr<ResourceManager>(new core::ResourceManager(this,m_iapp->getAppDescriptor().resourceFile));
				m_sceneManager = uptr<scn::SceneManager>(new scn::SceneManager(this));
				m_sceneManager->addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				LOG_DEBUG(appId() << ": " << " is now executing");
			}
				break;
			case lib::core::Host::AppState::Executing:
			{
				if (loopStep())
				{
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
				}

				exit = (m_iapp == nullptr);
			}

			if (!m_iapp) {
				LOG_INFO("App destroyed. Exiting normally");
			}
			return 0;
		}

		bool Host::loopStep()
		{
			bool windowWants2Close = m_window->preLoop();
			m_sceneManager->update();
			windowWants2Close |= m_window->postLoop();
			return windowWants2Close;
		}

		const std::string Host::appId() const
		{
			if (m_iapp)
			{
				return std::string(m_iapp->getAppDescriptor().Name + ":" + std::to_string(m_iapp->getAppDescriptor().Version) +
					"." + std::to_string(m_iapp->getAppDescriptor().SubVersion) + "."+std::to_string(m_iapp->getAppDescriptor().Patch));
			}
			return "NoApp:0.0.0";
		}

	}
}
