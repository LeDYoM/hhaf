#include "scenemanager.hpp"
#include "scene.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>

namespace lib
{
	namespace scn
	{
		SceneManager::SceneManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		SceneManager::~SceneManager()
		{
			for (auto scene : _scenes)
			{
				scene->privateOnDeinit();
			}
			_scenes.clear();
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			newScene->p_scnManager = this;
			_scenes.push_back(newScene);
			newScene->privateOnInit();
		}
	
		void SceneManager::setScene(const std::string &name)
		{
			if (sptr<Scene> scene = getSceneByName(name)) {
				setScene(std::move(scene));
				LOG_DEBUG("Changed scene to " << name);
			}
			else {
				LOG_ERROR("Scene " << name << " not found in SceneManager");
			}
		}
		
		void SceneManager::addScenes(const std::vector<sptr<Scene>>&& sceneVector)
		{
			for (auto scene : sceneVector)
			{
				addScene(scene);
			}
		}

		void SceneManager::setScene(sptr<Scene> scene)
		{
			__ASSERT(scene, "Cannot change to a nullptr Scene");
			if (_currentScene) {
				_currentScene->privateOnExitScene();
			}
			else {
				LOG_DEBUG("Set first scene");
			}
			_currentScene = scene;
			_currentScene->privateOnEnterScene();
		}

		sptr<Scene> SceneManager::getSceneByName(const std::string &name) const
		{
			const auto iterator(std::find_if(_scenes.cbegin(), _scenes.cend(), [&name](const auto&scene)
			{
				return scene->name() == name;
			}));
			return iterator == _scenes.end() ? nullptr : *iterator;
		}

		void SceneManager::update()
		{
			if (!_currentScene) {
				if (_scenes.size() > 0) {
					setScene(_scenes[0]);
				}
			}
			else {
				_currentScene->update();
			}

			sf::RenderStates states;
			_currentScene->draw(states);
		}

		void SceneManager::exitProgram()
		{
//			p_parentWindow->exitProgram();
		}

	}
}
