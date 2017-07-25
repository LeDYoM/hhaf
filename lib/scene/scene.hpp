#ifndef LIB_DRAW_SCENE_HPP__
#define LIB_DRAW_SCENE_HPP__

#pragma once

#include "hasname.hpp"
#include "scenenode.hpp"

#include <mtypes/include/types.hpp>
#include <lib/core/timer.hpp>
#include <lib/core/events/event.hpp>
#include <lib/core/events/eventreceiver.hpp>

namespace lib
{
	namespace core
	{
		class Host;
	}
	namespace scene
	{
		class SceneNode;

		class Scene : public scene::SceneNode
		{
		public:
			Scene(str name);
			virtual ~Scene();

			virtual void onInit();
			virtual void onDeinit();
			virtual void onEnterScene();
			virtual void onExitScene();

			virtual void updateScene() = 0;

			inline bool isActiveScene() const noexcept { return m_isActiveScene; }
			inline void addSubscription(sptr<events::EventSubscription> &&es) noexcept { eventConnector.addSubscription(std::move(es)); }
			virtual Scene *const parentScene() noexcept override { return this; }

		protected:

			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }
			Timer clock;
			EventReceiver eventConnector;

			inline void setAsActiveScene(const bool nv) noexcept { m_isActiveScene = nv; }

			u32 _state;
			bool m_isActiveScene{ false };

			friend class core::Host;
			friend class SceneManager;
		};
	}
}

#endif
