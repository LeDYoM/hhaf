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
		class SceneManager;

		class Scene : public scene::SceneNode
		{
		public:
			Scene(str name);
			virtual ~Scene();

			void create() override;
			virtual void updateScene() {}

			inline void addSubscription(sptr<events::EventSubscription> &&es) noexcept { eventConnector.addSubscription(std::move(es)); }
			virtual Scene *const parentScene() noexcept override { return this; }

			inline SceneManager &sceneManager() noexcept { return *m_sceneManager; }
			inline const SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

		protected:

			inline u32 state() const { return _state; }
			inline void setState(u32 ns) { _state = ns; }

			Timer clock;
			EventReceiver eventConnector;

			u32 _state;

		private:
			SceneManager *m_sceneManager{ nullptr };
			friend class core::Host;
			friend class SceneManager;
		};
	}
}

#endif
