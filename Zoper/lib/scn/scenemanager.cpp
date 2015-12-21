#include "scenemanager.hpp"
#include "scene.hpp"
#include "../log.hpp"
#include "../core/window.hpp"
#include "resourcemanager.hpp"

namespace lib
{
	namespace scn
	{
		SceneManager::SceneManager(core::Window *pParentWindow, const std::string &resFile)
		{
			LOG_CONSTRUCT_NOPARAMS;
			p_parentWindow = pParentWindow;
			__ASSERT(p_parentWindow, "Cannot create a scene manager from null window");

			_resourceManager = std::make_unique<ResourceManager>(resFile);
		}

		SceneManager::~SceneManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERTERROR(newScene, "Cannot add a null scene");
			newScene->p_scnManager = this;
			_scenes.push_back(newScene);
			newScene->privateOnInit();
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

		void SceneManager::onKeyPressed(sf::Event::KeyEvent kEvent)
		{
			__ASSERT(_currentScene, "No active scene when pressing a key");
			_currentScene->onKeyPressed(kEvent);
		}

		void SceneManager::onKeyReleased(sf::Event::KeyEvent kEvent)
		{
			__ASSERT(_currentScene, "No active scene when releasing a key");
			_currentScene->onKeyReleased(kEvent);
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
				LOG_DEBUG("Set first scene");
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
				_nextScene = nullptr;
			}
			else
			{
				_currentScene->update();
			}

			_currentScene->draw(p_parentWindow);
		}
	}
}
