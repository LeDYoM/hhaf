#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/core/timer.hpp>
#include "rendergroup.hpp"
#include <string>
#include <SFML/Window/Event.hpp>

namespace lib
{
	namespace core
	{
		class ResourceManager;
	}
	namespace scn
	{
		class SceneManager;
		namespace draw
		{
			class RenderGroup;
			namespace anim
			{
				class IAnimation;
			}
		}

		class Scene : public draw::RenderGroup
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

			virtual const vector2df getDefaultSizeView() = 0;
			uptr<core::ResourceManager> const &resourceManager();
			const vector2df getCoordinatesToCenter(const sf::FloatRect &coordinates) const;
			const vector2df getCenterCoordinates() const;

			void exitProgram();

		protected:

			void updateView();
			sf::View *const getView() const;
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

			Timer clock;
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
