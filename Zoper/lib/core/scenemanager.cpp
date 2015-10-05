#include "scenemanager.hpp"
#include "scene.hpp"
#include "../log.hpp"

namespace lib
{
	namespace core
	{
		SceneManager::SceneManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}


		SceneManager::~SceneManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::addScene(std::shared_ptr<Scene> newScene)
		{
			_scenes.push_back(newScene);
			newScene->p_scnManager = this;
		}
	
		void SceneManager::setScene(const std::string &name)
		{
			std::shared_ptr<Scene> scene = getSceneByName(name);
			
			if (scene)
			{
				if (b_lock)
				{
					_nextScene = scene;
					LOG_DEBUG("Deferred Change scene to " << name);
				}
				else
				{
					b_lock = true;
					setScene(scene);
					b_lock = false;
				}
			}
			else
			{
				LOG_ERROR("Scene "<<name<<" not found in SceneManager");
			}
		}
		
		void SceneManager::setScene(std::shared_ptr<Scene> scene)
		{
			__ASSERT(scene, "Cannot change to a nullptr Scene");
			if (_currentScene)
			{
				_currentScene->onExitScene();
			}
			else
			{
				LOG_DEBUG("Scene was empty");
			}
			_currentScene = scene;
			_currentScene->onEnterScene();
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

			if (_nextScene)
			{
				setScene(_nextScene);
			}
		}
	}
}
