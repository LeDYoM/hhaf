#include "host.hpp"
#include "window.hpp"
#include "resourcemanager.hpp"
#include "log.hpp"
#include "randomizer.hpp"
#include <lib/draw/scene.hpp>
#include <lib/draw/renderstatesstack.hpp>
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/inputsystem.hpp>
#include <lib/backend/backendfactory.hpp>
#include <lib/backend/iwindow.hpp>
#include "config.h"

#include <algorithm>

namespace lib
{
	namespace core
	{
		auto transformParams(int argc, char *argv[])
		{
			std::vector<std::string> temp;

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
			logConstruct_NOPARAMS;
			logInfo("Starting HostController...");
			logInfo("LIB version: ", LIB_VERSION_MAJOR,".", LIB_VERSION_MINOR,".", LIB_VERSION_PATCH);
			backend::BackendFactory bf;
			logInfo("Using backend: ");
			logInfo(bf.getWindowProviderInfo()->info());
			logInfo("Parsing parameters...");
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
				logDebug("Starting app ", appId(), "...");
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
				logDebug(appId(), ": ", " Starting initialization...");
				m_state = AppState::Executing;

				m_inputSystem = muptr<input::InputSystem>();
				m_randomizer = muptr<Randomizer>();
				m_eventManager = muptr<EventManager>();
				m_window = muptr<Window>(m_iapp->getAppDescriptor().wcp);
				m_resourceManager = muptr<core::ResourceManager>(m_iapp->getAppDescriptor().resourceFile);
				m_renderStates = muptr<draw::RenderStatesStack>();
				
				addScenes(m_iapp->scenesVector());

				m_iapp->onInit();
				logDebug(appId(), ": ", " is now executing");
			}
				break;
			case AppState::Executing:
			{
				if (loopStep()) {
					m_state = AppState::ReadyToTerminate;
					logDebug(appId(), ": ", " is now ready to terminate");
				}
				else if (m_state == AppState::ReadyToTerminate) {
					logDebug(appId(), ": ", " requested to terminate");
				}
			}
				break;
			case AppState::ReadyToTerminate:
				logDebug(appId(), ": " ," started termination");
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
				m_window = nullptr;
				m_resourceManager = nullptr;
				m_eventManager = nullptr;
				m_randomizer = nullptr;
				m_inputSystem = nullptr;
				m_params.clear();
				logDebug(appId(), ": ", " terminated");
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
				logInfo("App destroyed. Exiting normally");
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

		const std::string Host::appId() const
		{
			using std::string;
			using std::to_string;

			if (m_iapp) {
				return string(
					string(m_iapp->getAppDescriptor().Name) + ":" + 
					to_string(m_iapp->getAppDescriptor().Version) + "." + 
					to_string(m_iapp->getAppDescriptor().SubVersion) + "." + 
					to_string(m_iapp->getAppDescriptor().Patch)
				);
			}
			return "NoApp:0.0.0";
		}

		void Host::addScene(sptr<draw::Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			m_scenes.push_back(newScene);
			newScene->onInit();
		}

		void Host::setScene(const std::string &name)
		{
			if (sptr<draw::Scene> scene = getSceneByName(name)) {
				setScene(std::move(scene));
				logDebug("Changed scene to ", name);
			}
			else {
				logError("Scene ", name, " not found in scenes");
			}
		}

		void Host::addScenes(std::vector<sptr<draw::Scene>>&& sceneVector)
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
					logDebug("Set first scene");
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

		void Host::setScene(sptr<draw::Scene> &&scene)
		{
			m_nextScene = std::move(scene);
		}

		sptr<draw::Scene> Host::getSceneByName(const std::string &name) const
		{
			const auto iterator(std::find_if(m_scenes.cbegin(), m_scenes.cend(), [&name](const auto&scene)
			{
				return scene->name() == name;
			}));
			return iterator == m_scenes.cend() ? nullptr : *iterator;
		}
	}
}
