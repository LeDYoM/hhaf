#ifndef LIB_DRAW_SCENE_HPP__
#define LIB_DRAW_SCENE_HPP__

#pragma once

#include "hasname.hpp"
#include "scenenode.hpp"

#include <lib/include/types.hpp>
#include <lib/core/timer.hpp>
#include <lib/core/events/event.hpp>
#include <lib/core/events/eventreceiver.hpp>
#include <lib/draw/view.hpp>

namespace lib
{
	namespace core
	{
		class Host;
	}
	namespace draw
	{
		class SceneNode;

		class Scene : public draw::SceneNode
		{
		public:
			Scene(str_const name);
			virtual ~Scene();

			virtual void onInit();
			virtual void onDeinit();
			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void updateScene() = 0;

			virtual vector2df getDefaultSizeView() = 0;
			vector2df getCoordinatesToCenter(const Rectf32 &coordinates) const;
			vector2df getCenterCoordinates() const;

			inline bool isActiveScene() const noexcept { return m_isActiveScene; }
			inline void addSubscription(sptr<events::EventSubscription> &&es) noexcept { eventConnector.addSubscription(std::move(es)); }
			virtual Scene *const parentScene() noexcept override { return this; }
			ForwardProperty<Rectf32> viewPort;
			ForwardProperty<Rectf32> viewRect;

		protected:

			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
			Timer clock;
			EventReceiver eventConnector;

			inline void setAsActiveScene(const bool nv) noexcept { m_isActiveScene = nv; }

			u32 _state;
			bool m_isActiveScene{ false };

			friend class lib::core::Host;
		};
	}
}

#endif
