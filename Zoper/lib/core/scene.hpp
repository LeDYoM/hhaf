#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <memory>
#include "../compileconfig.hpp"
#include "../types.hpp"

#include <SFML/Graphics.hpp>

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
			void draw(const sf::Drawable &drawable);

			sptr<sf::Text> createText();
		private:
			std::vector<sptr<sf::Drawable>> v_nodes;
			uptr<sf::View> p_view;

			static wptr<SceneManager> p_scnManager;
			friend class SceneManager;
			friend class ProgramController;
		};
	}
}

#endif
