#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/core/appservice.hpp>

namespace lib
{
	namespace scene
	{
		class SceneManager : public AppService
		{
		public:
			SceneManager();
			~SceneManager();

		};
	}
}

#endif
