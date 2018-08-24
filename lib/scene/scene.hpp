#pragma once

#ifndef LIB_SCENE_SCENE_INCLUDE_HPP__
#define LIB_SCENE_SCENE_INCLUDE_HPP__

#include "hasname.hpp"
#include "scenenode.hpp"

#include <mtypes/include/types.hpp>
#include <lib/include/core/timer.hpp>
#include <lib/scene/components/statescontroller.hpp>

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

			virtual Scene *const parentScene() noexcept override { return this; }

			inline SceneManager &sceneManager() noexcept { return *m_sceneManager; }
			inline const SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

		protected:

            size_type state();
			void setState(const size_type);
            sptr<StatesController<size_type>> m_sceneStates;

		private:

            SceneManager *m_sceneManager{ nullptr };
			friend class core::Host;
			friend class SceneManager;
		};
	}
}

#endif
