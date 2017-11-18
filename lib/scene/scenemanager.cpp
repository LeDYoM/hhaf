#include "scenemanager.hpp"
#include <mtypes/include/log.hpp>
#include "scene.hpp"

namespace lib
{
	namespace scene
	{
		SceneManager::SceneManager(core::Window &window) : m_parentWindow{ window } {}

		SceneManager::~SceneManager() = default;

		void SceneManager::start(sptr<Scene> scene)
		{
			m_componentContainer.ensureComponentOfType(m_statesController);
			m_statesController->UseDeferred();
			scene->create();
			m_statesController->start(std::move(scene));
		}

		void SceneManager::terminateScene()
		{
			sptr<Scene> nextScene;
			if (m_sceneDirector) {
				nextScene = m_sceneDirector(m_statesController->currentState());
			}
			m_statesController->setState(nextScene);
		}

		void SceneManager::setSceneDirector(SceneDirectorType sceneDirector)
		{
			m_sceneDirector = std::move(sceneDirector);
		}

		void SceneManager::update()
		{
			m_componentContainer.updateComponents();
			if (auto&& currentScene = m_statesController->currentState(); currentScene) {
				currentScene->updateScene();
				currentScene->render(false);
			}
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
			m_statesController->pop_state();
		}
	}
}
