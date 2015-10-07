#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <memory>
#include "../compileconfig.hpp"
#include "../types.hpp"

namespace lib
{
	namespace core
	{
		class SceneManager;
		class Window;
		class Scene : public HasName
		{
		public:
			Scene(const std::string &name);
			virtual ~Scene();

			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void update() = 0;

			void setNextScene(const std::string &name);
		private:
			SceneManager *p_scnManager;
			Window *p_parentWindow;
			friend class SceneManager;
		};
	}
}

#endif
