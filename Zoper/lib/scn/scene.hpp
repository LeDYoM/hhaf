#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "../core/hasname.hpp"
#include <memory>
#include "../compileconfig.hpp"
#include "../types.hpp"

#include <SFML/Graphics.hpp>


namespace lib
{
	namespace core
	{
		class Window;
		class ProgramController;
	}

	namespace scn
	{
		namespace draw
		{
			class Renderizable;
		}

		class SceneManager;

		class Scene : public lib::core::HasName
		{
		public:
			Scene(const std::string &name);
			virtual ~Scene();

			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void update() = 0;

			void setNextScene(const std::string &name);

			sptr<draw::Renderizable> createText(const std::string &name);
			sptr<draw::Renderizable> createSprite(const std::string &name);
			sptr<draw::Renderizable> createShape(const std::string &name);
			sptr<draw::Renderizable> addRenderizable(sptr<draw::Renderizable> newElement);

			u32 getRandomNumer(u32 max = 1, u32 min = 0);
		protected:

			void updateView();
			sf::View *const getView() const;
		private:
			u32 drawAll();
			std::vector<sptr<draw::Renderizable>> v_nodes;
			uptr<sf::View> p_view;

			static wptr<SceneManager> p_scnManager;
			friend class SceneManager;
			friend class lib::core::ProgramController;
		};
	}
}

#endif
