#ifndef LIB_DRAW_SCENE_HPP__
#define LIB_DRAW_SCENE_HPP__

#pragma once

#include "hasname.hpp"
#include "scenenode.hpp"

#include <mtypes/include/types.hpp>
#include <lib/scene/components/statescontroller.hpp>
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
		class SceneManager;

		class Scene : public SceneNode
		{
		public:
			Scene(str name);
			virtual ~Scene();

			void onCreated() override;
			virtual void updateScene() {}

			inline void addSubscription(sptr<events::EventSubscription> &&es) noexcept { eventConnector.addSubscription(std::move(es)); }
			virtual Scene *const parentScene() noexcept override { return this; }

			inline SceneManager &sceneManager() noexcept { return *m_sceneManager; }
			inline const SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

		protected:

            u32 state();
            void setState(const size_type ns);

			Timer clock;
			EventReceiver eventConnector;

		private:
            sptr<StatesController<size_type>> m_sceneStates;
            SceneManager *m_sceneManager{ nullptr };
			friend class core::Host;
			friend class SceneManager;
		};
	}
}

#endif
