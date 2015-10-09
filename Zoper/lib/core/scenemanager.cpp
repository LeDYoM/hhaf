#include "scenemanager.hpp"
#include "scene.hpp"
#include "../log.hpp"
#include "window.hpp"

namespace lib
{
	namespace core
	{
		wptr<Window> SceneManager::p_parentWindow;

		SceneManager::SceneManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		SceneManager::~SceneManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			_scenes.push_back(newScene);
		}
	
		void SceneManager::setScene(const std::string &name)
		{
			sptr<Scene> scene = getSceneByName(name);
			
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
		
		void SceneManager::setScene(sptr<Scene> scene)
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

		sptr<Scene> SceneManager::getSceneByName(const std::string &name) const
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
			else if (_nextScene)
			{
				setScene(_nextScene);
			}
			else
			{
				_currentScene->update();
			}

			_currentScene->drawAll();
		}
	}
}
