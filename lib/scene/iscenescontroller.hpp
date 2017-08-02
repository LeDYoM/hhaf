#ifndef LIB_SCENE_ISCENESCONTROLLER_INCLUDE_HPP__
#define LIB_SCENE_ISCENESCONTROLLER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>

namespace lib
{
	namespace scene
	{
		class Scene;
		class SceneManager;
		class IScenesController
		{
		public:
			IScenesController(SceneManager &scnManager) : sceneManager{ scnManager } {}
			virtual ~IScenesController() {};

			virtual sptr<Scene> startScene() = 0;
			virtual sptr<Scene> scenedFinished(sptr<Scene>) = 0;
		private:
			SceneManager &sceneManager;
		};
	}
}

#endif
