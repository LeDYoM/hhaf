#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>

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

			void addScene(Scene *newScene);
			void setScene(Scene *scene);
			void setScene(const std::string &name);
		private:
			Scene *getSceneByName(const std::string &name) const;
			std::vector<Scene*> _scenes;
			Scene *_currentScene;
		};
	}
}

#endif
