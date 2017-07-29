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
			IScenesController() {};
			virtual ~IScenesController() {};

			virtual sptr<Scene> scenedFinished(SceneManager &sceneManager, sptr<Scene>) = 0;
		};
	}
}

#endif
