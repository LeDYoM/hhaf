#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <memory>
#include "../compileconfig.hpp"

namespace lib
{
	namespace core
	{
		class SceneManager;
		class Scene : public HasName
		{
		public:
			Scene(const std::string &name);
			virtual ~Scene();

			virtual void onEnterScene();
			virtual void onExitScene();

			void setNextScene(const std::string &name);
		private:
			SceneManager *p_scnManager{ nullptr };
			friend class SceneManager;
		};
	}
}

#endif
