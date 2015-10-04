#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <memory>

namespace lib
{
	namespace core
	{
		class Scene : public HasName
		{
		public:
			Scene(const std::string &name);
			virtual ~Scene();

			virtual void onEnterScene();
			virtual void onExitScene();
		};

		using ScenePtr = std::shared_ptr<Scene>;
	}
}

#endif
