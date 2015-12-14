#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "../core/hasname.hpp"
#include <string>
#include "../compileconfig.hpp"
#include "../types.hpp"
#include "draw/rendergroup.hpp"

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
		class SceneManager;
		class ResourceManager;

		class Scene : public lib::core::HasName, public draw::RenderGroup
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

			u32 getRandomNumer(u32 max = 1, u32 min = 0);
		protected:

			void updateView();
			sf::View *const getView() const;
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
			uptr<ResourceManager> &resourceManager();

			sf::Clock clock;
		private:
			void privateOnInit();
			void privateOnDeinit();
			void privateOnEnterScene();
			void privateOnExitScene();

			uptr<sf::View> p_view;
			u32 _state;

			SceneManager *p_scnManager;
			friend class SceneManager;
		};
	}
}

#endif
