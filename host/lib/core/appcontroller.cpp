#include "appcontroller.hpp"
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
		AppController::AppController(uptr<IApp> iapp)
			: m_iapp( std::move(iapp) )
		{
			LOG_CONSTRUCT_NOPARAMS;
			LOG_DEBUG("Starting app " << appId() << "...");
			m_state = AppState::ReadyToStart;
		}

		AppController::~AppController()
		{
			LOG_DESTRUCT("Name: " << appId());
		}

		bool AppController::update()
		{
			switch (m_state)
			{
			case lib::core::AppController::AppState::NotInitialized:
				break;
			case lib::core::AppController::AppState::ReadyToStart:
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
			case lib::core::AppController::AppState::Executing:
			{
				if (loopStep())
				{
					m_state = AppState::ReadyToTerminate;
					LOG_DEBUG(appId() << ": " << " is now ready to terminate");
				}
			}
				break;
			case lib::core::AppController::AppState::ReadyToTerminate:
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
			case lib::core::AppController::AppState::Terminated:
				return true;
				break;
			default:
				break;
			}
			return false;
		}

		bool AppController::loopStep()
		{
			bool windowWants2Close = m_window->preLoop();
			m_sceneManager->update();
			windowWants2Close |= m_window->postLoop();
			return windowWants2Close;
		}

		const std::string AppController::appId() const
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
