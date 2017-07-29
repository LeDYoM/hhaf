#include "scenemanager.hpp"
#include <mtypes/include/log.hpp>
#include "scene.hpp"
#include "renderstatesstack.hpp"
#include <lib/core/window.hpp>

namespace lib
{
	namespace scene
	{
		SceneManager::SceneManager(core::Window &window) : m_parentWindow{ window }, 
			viewPort{ dynamic_cast<IProperty<Rectf32>*>(&(window.viewPort)) },
			viewRect{ dynamic_cast<IProperty<Rectf32>*>(&(window.viewRect)) }
		{
		}

		SceneManager::~SceneManager() = default;

		void SceneManager::updateScene()
		{
			if (m_nextScene) {
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

		void SceneManager::addScenes(vector<sptr<Scene>>&& sceneVector)
		{
			for (auto &scene : sceneVector) {
				addScene(std::move(scene));
			}
		}

		void SceneManager::setScene(sptr<Scene> scene)
		{
			m_nextScene = std::move(scene);
			if (m_nextScene) m_nextScene->create();
		}

		void SceneManager::terminateScene()
		{
			setScene(nullptr);
		}

		sptr<Scene> SceneManager::getSceneByName(const str &name) const
		{
			const auto iterator(std::find_if(m_scenes.cbegin(), m_scenes.cend(), [&name](const auto&scene)
			{
				return scene->name() == name;
			}));
			return iterator == m_scenes.cend() ? nullptr : *iterator;
		}

		void SceneManager::update()
		{
			updateScene();

			m_renderStates.newFrame();
			m_currentScene->draw();
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			m_scenes.push_back(newScene);
			newScene->create();

//			m_debugSystem->addDebugVars(newScene);
		}

		void SceneManager::finish()
		{
			if (m_currentScene) {
				m_currentScene->onExitScene();
			}
			m_currentScene = nullptr;
			for (auto &scene : m_scenes) {
				scene->onDeinit();
			}
			m_scenes.clear();
		}

	}
}
