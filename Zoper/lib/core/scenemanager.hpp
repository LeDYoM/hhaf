#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include "../types.hpp"

namespace lib
{
	namespace core
	{
		class Scene;
		class SceneManager
		{
		public:
			SceneManager();
			virtual ~SceneManager();

			void addScene(sptr<Scene> newScene);
			void setScene(const std::string &name);
			void update();
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
