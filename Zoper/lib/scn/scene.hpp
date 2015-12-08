#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "../core/hasname.hpp"
#include <string>
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
		class ResourceManager;

		class Scene : public lib::core::HasName
		{
		public:
			Scene(const std::string &_name);
			virtual ~Scene();

			virtual void onInit() = 0;
			virtual void onDeinit() = 0;
			virtual void onEnterScene() = 0;
			virtual void onExitScene() = 0;

			virtual void update() = 0;

			virtual void onKeyPressed(sf::Event::KeyEvent kEvent);
			virtual void onKeyReleased(sf::Event::KeyEvent kEvent);

			void setNextScene(const std::string &name);

			sptr<draw::Renderizable> createText(const std::string &name);
			sptr<draw::Renderizable> createSprite(const std::string &name);
			sptr<draw::Renderizable> createShape(const std::string &name);
			sptr<draw::Renderizable> addRenderizable(sptr<draw::Renderizable> newElement);
			bool removeRenderizable(sptr<draw::Renderizable> element);

			u32 getRandomNumer(u32 max = 1, u32 min = 0);
//			uptr<ResourceManager> &resourceManager();
		protected:

			void updateView();
			sf::View *const getView() const;
		private:
			void privateOnInit();
			void privateOnDeinit();
			void privateOnEnterScene();
			void privateOnExitScene();
			u32 drawAll();
			std::vector<sptr<draw::Renderizable>> v_nodes;
			uptr<sf::View> p_view;

			SceneManager *p_scnManager;
			friend class SceneManager;
		};
	}
}

#endif
