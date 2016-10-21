#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/core/timer.hpp>
#include "rendergroup.hpp"
#include <lib/include/event.hpp>
#include <lib/core/events/eventreceiver.hpp>
#include <string>
#include <SFML/Window/Event.hpp>

namespace lib
{
	namespace core
	{
		class ResourceManager;
		class Host;
	}
	namespace scn
	{
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

			virtual const vector2df getDefaultSizeView() = 0;
			const vector2df getCoordinatesToCenter(const sf::FloatRect &coordinates) const;
			const vector2df getCenterCoordinates() const;

		protected:

			void updateView();
			sf::View *const getView() const;
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

			bool isActiveScene() const noexcept { return m_isActiveScene; }

			Timer clock;
		private:
			void privateOnInit();
			void privateOnDeinit();
			void privateOnEnterScene();
			void privateOnExitScene();

			inline void setAsActiveScene(const bool nv) noexcept { m_isActiveScene = nv; }

			uptr<sf::View> p_view;
			u32 _state;
			bool m_isActiveScene{ false };
			core::events::EventReceiver eventConnector;

			friend class lib::core::Host;
		};
	}
}

#endif
