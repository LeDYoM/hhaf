#include "scenemanager.hpp"
#include <mtypes/include/log.hpp>
#include "scene.hpp"

namespace lib
{
	namespace scene
	{
		SceneManager::SceneManager(core::Window &window) : m_parentWindow{ window } {}

		SceneManager::~SceneManager() = default;

		void SceneManager::startScene(sptr<Scene> scene)
		{
			m_componentContainer.ensureComponentOfType(m_statesController);
			m_statesController->UseDeferred();
			m_statesController->start(std::move(scene));
		}

		void SceneManager::setScene(sptr<Scene> scene)
		{
			m_statesController->setState(std::move(scene));
		}

		void SceneManager::update()
		{
			/*
			if (m_nextScene) {
				if (m_currentScene) {
					m_currentScene->onDeinit();
				}
				else {
					log_debug_info("Set first scene");
				}

				m_currentScene = m_nextScene;
				m_nextScene = nullptr;

				m_currentScene->create();
			}
			else {
				m_currentScene->updateScene();
			}

			m_currentScene->render(false);
			*/
		}

		void SceneManager::finish()
		{
			if (m_currentScene) {
//				m_currentScene->onDeinit();
			}
			m_currentScene = nullptr;
		}
	}
}
