#include "host.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include <mtypes/include/log.hpp>
#include "randomizer.hpp"
#include <lib/scene/scene.hpp>
#include <lib/scene/renderstatesstack.hpp>
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/backend/backendfactory.hpp>
#include <lib/backend/iwindow.hpp>
#include <lib/core/debugsystem.hpp>

#include "config.h"

#include <algorithm>

namespace lib
{
	namespace core
	{
		auto transformParams(int argc, char *argv[])
		{
			vector<str> temp;

			for (int i = 1; i<argc; ++i) {
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
			: m_state{ AppState::NotInitialized }
		{
			logConstruct_NOPARAMS;
			log_release_info("Starting HostController...");
			log_release_info("LIB version: ", LIB_VERSION_MAJOR,".", LIB_VERSION_MINOR,".", LIB_VERSION_PATCH);
			log_release_info("Parsing parameters...");
			m_params = transformParams(argc, argv);
		}

		Host::~Host()
		{
			logDestruct_NOPARAMS;
		}

		bool Host::setApplication(uptr<IApp> iapp)
		{
			if (!m_iapp && iapp) {
				std::swap(m_iapp, iapp);
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
				log_debug_info(appId(), ": ", " Starting initialization...");
				m_state = AppState::Executing;

				m_inputSystem = muptr<input::InputSystem>();
				m_randomizer = muptr<Randomizer>();
				m_eventManager = muptr<EventManager>();
				m_window = muptr<Window>(m_iapp->getAppDescriptor().wcp);
				m_resourceManager = muptr<core::ResourceManager>(m_iapp->getAppDescriptor().resourceFile);
				m_renderStates = muptr<scene::RenderStatesStack>();
				m_debugSystem = muptr<DebugSystem>();
				
				addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				log_debug_info(appId(), ": ", " is now executing");
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
				log_debug_info(appId(), ": " ," started termination");
				if (m_currentScene) {
					m_currentScene->onExitScene();
				}
				m_currentScene = nullptr;
				for (auto &scene : m_scenes) {
					scene->onDeinit();
				}
				m_scenes.clear();
				m_state = AppState::Terminated;
//				m_iapp->onFinish();
				m_debugSystem = nullptr;
				m_window = nullptr;
				m_resourceManager = nullptr;
				m_eventManager = nullptr;
				m_randomizer = nullptr;
				m_inputSystem = nullptr;
				m_params.clear();
				log_debug_info(appId(), ": ", " terminated");
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
				bool terminated{ update() };
				if (terminated) {
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
			bool windowWants2Close = m_window->preLoop();
			m_eventManager->update();
			m_inputSystem->preUpdate();

			__ASSERT(m_currentScene || m_nextScene, "Current scene and nextscene cannot be nullptr at same time");
			updateScene();

			m_renderStates->newFrame();
			m_currentScene->draw();

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
				return 
					str(m_iapp->getAppDescriptor().Name) + ":" + 
					(m_iapp->getAppDescriptor().Version) + "." + 
					(m_iapp->getAppDescriptor().SubVersion) + "." + 
					(m_iapp->getAppDescriptor().Patch)
				;
			}
			return "NoApp:0.0.0";
		}

		void Host::addScene(sptr<scene::Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			m_scenes.push_back(newScene);
			newScene->onInit();

			m_debugSystem->addDebugVars(newScene);
		}

		void Host::setScene(const str &name)
		{
			if (sptr<scene::Scene> scene = getSceneByName(name)) {
				setScene(std::move(scene));
				log_debug_info("Changed scene to ", name);
			}
			else {
				log_debug_error("Scene ", name, " not found in scenes");
			}
		}

		void Host::addScenes(vector<sptr<scene::Scene>>&& sceneVector)
		{
			for (auto &scene : sceneVector) {
				addScene(std::move(scene));
			}
		}

		void Host::updateScene()
		{
			if (m_nextScene)
			{
				if (m_currentScene) {
					m_currentScene->onExitScene();
				}
				else {
					log_debug_info("Set first scene");
				}
				if (m_currentScene) m_currentScene->setAsActiveScene(false);
				m_nextScene->setAsActiveScene(true);

				m_currentScene = m_nextScene;
				m_nextScene = nullptr;

				m_currentScene->onEnterScene();
			}
			else {
				m_currentScene->updateScene();
			}
		}

		void Host::setScene(sptr<scene::Scene> &&scene)
		{
			m_nextScene = std::move(scene);
		}

		sptr<scene::Scene> Host::getSceneByName(const str &name) const
		{
			const auto iterator(std::find_if(m_scenes.cbegin(), m_scenes.cend(), [&name](const auto&scene)
			{
				return scene->name() == name;
			}));
			return iterator == m_scenes.cend() ? nullptr : *iterator;
		}
	}
}
