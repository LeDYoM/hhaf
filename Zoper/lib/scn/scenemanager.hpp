#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include "../types.hpp"
#include <SFML/Window/Event.hpp>

namespace lib
{
	namespace core
	{
		class Window;
		class ProgramController;
	}
	namespace scn
	{
		class Scene;
		class SceneManager
		{
		public:
			SceneManager(core::Window *pParentWindow);
			virtual ~SceneManager();

			void addScene(sptr<Scene> newScene);
			void setScene(const std::string &name);
			void update();

			const core::Window *parentWindow() const { return p_parentWindow; }
			core::Window *parentWindow() { return p_parentWindow; }

			void addScenes(const std::vector<sptr<Scene>> &&sceneVector);

			void onKeyPressed(sf::Event::KeyEvent kEvent);
			void onKeyReleased(sf::Event::KeyEvent kEvent);
		private:
			void setScene(sptr<Scene> scene);

			sptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<sptr<Scene>> _scenes;
			sptr<Scene> _currentScene{ nullptr };
			bool b_lock{ false };
			sptr<Scene> _nextScene{ nullptr };
			core::Window *p_parentWindow;
		};
	}
}

#endif
