#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include <memory>

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

			void addScene(std::shared_ptr<Scene> newScene);
			void setScene(std::shared_ptr<Scene> scene);
			void setScene(const std::string &name);
			void update();
		private:
			std::shared_ptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<std::shared_ptr<Scene>> _scenes;
			std::shared_ptr<Scene> _currentScene{ nullptr };
		};
	}
}

#endif
