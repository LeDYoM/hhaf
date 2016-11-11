#ifndef __LIB_SCENE_HPP__
#define __LIB_SCENE_HPP__

#include "hasname.hpp"
#include "rendergroup.hpp"

#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/core/timer.hpp>
#include <lib/core/events/event.hpp>
#include <lib/core/events/eventreceiver.hpp>
#include <string>

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

			virtual void onInit();
			virtual void onDeinit();
			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void update() = 0;

			virtual const vector2df getDefaultSizeView() = 0;
			const vector2df getCoordinatesToCenter(const sf::FloatRect &coordinates) const;
			const vector2df getCenterCoordinates() const;

			inline bool isActiveScene() const noexcept { return m_isActiveScene; }
			inline void addSubscription(lib::events::EventSubscription &&es) noexcept { eventConnector.addSubscription(std::move(es)); }

		protected:

			void updateView();
			sf::View *const getView() const;
			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
			Timer clock;
			EventReceiver eventConnector;
			virtual Scene *const parentScene() noexcept override { return this; }

			inline void setAsActiveScene(const bool nv) noexcept { m_isActiveScene = nv; }

			uptr<sf::View> p_view;
			u32 _state;
			bool m_isActiveScene{ false };

			friend class lib::core::Host;
		};
	}
}

#endif
