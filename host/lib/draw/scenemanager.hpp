#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <SFML/Window/Event.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace scn
	{
		class ResourceManager;
		class Scene;

		class SceneManager : public AppService
		{
		public:
			SceneManager(const SceneManager &rh) = delete;
			SceneManager(core::AppController *const appController);
			virtual ~SceneManager();

			void addScene(sptr<Scene> newScene);
			void setScene(const std::string &name);
			void update();

			void addScenes(const std::vector<sptr<Scene>> &&sceneVector);

			void onKeyPressed(sf::Event::KeyEvent kEvent);
			void onKeyReleased(sf::Event::KeyEvent kEvent);
			void exitProgram();

		private:
			void setScene(sptr<Scene> scene);

			sptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<sptr<Scene>> _scenes;
			sptr<Scene> _currentScene{ nullptr };
			bool b_lock{ false };
			sptr<Scene> _nextScene{ nullptr };
		};
	}
}

#endif
