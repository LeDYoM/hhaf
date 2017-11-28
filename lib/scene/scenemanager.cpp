#include "scenemanager.hpp"
#include <mtypes/include/log.hpp>
#include "scene.hpp"

namespace lib
{
	namespace scene
	{
		SceneManager::SceneManager(core::Window &window) : m_parentWindow{ window } {}

		SceneManager::~SceneManager() = default;

		void SceneManager::start()
		{
			m_componentContainer.ensureComponentOfType(m_statesController);
			m_statesController->UseDeferred();
		}

		void SceneManager::terminateScene()
		{
			sptr<Scene> nextScene;
			if (m_sceneDirector) {
				nextScene = m_sceneDirector(m_statesController->currentState());
			}
			m_statesController->setState(std::move(nextScene));
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
                int b = 0;
			}
		}

		void SceneManager::finish()
		{
			m_statesController->pop_state();
		}
	}
}
