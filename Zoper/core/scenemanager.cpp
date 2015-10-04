#include "scenemanager.hpp"
#include "scene.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		SceneManager::SceneManager()
		{
		}


		SceneManager::~SceneManager()
		{
		}

		void SceneManager::addScene(std::shared_ptr<Scene> newScene)
		{
			_scenes.push_back(newScene);
		}

		void SceneManager::setScene(std::shared_ptr<Scene> newScene)
		{
			if (_currentScene)
			{
				_currentScene->onExitScene();
			}
			else
			{
				LOG_DEBUG("Scene was empty");
			}
			_currentScene = newScene;
			_currentScene->onEnterScene();
		}
		
		void SceneManager::setScene(const std::string &name)
		{
			std::shared_ptr<Scene> scene = getSceneByName(name);
			
			if (scene)
			{
				setScene(scene);
			}
			else
			{
				LOG_ERROR("Scene "<<name<<" not found in SceneManager");
			}
		}
		
		std::shared_ptr<Scene> SceneManager::getSceneByName(const std::string &name) const
		{
			for (auto scene : _scenes)
			{
				if (scene->name() == name)
				{
					return scene;
				}
			}
			return nullptr;
		}

		void SceneManager::update()
		{
			if (!_currentScene)
			{
				setScene(_scenes[0]);
			}
		}
	}
}
