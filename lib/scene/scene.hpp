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
    class IResourceLoader;

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
			virtual void onFinished() {}

			virtual void updateScene() {}

			Scene *const parentScene() noexcept override { return this; }
            const Scene *const parentScene() const noexcept override { return this; }

			inline SceneManager &sceneManager() noexcept { return *m_sceneManager; }
			inline const SceneManager &sceneManager() const noexcept { return *m_sceneManager; }

            void loadResources(IResourceLoader &&resourceloader);
		protected:

            size_type state();
			void setState(const size_type);
            sptr<StatesController<size_type>> m_sceneStates;

		private:

            SceneManager *m_sceneManager{ nullptr };
			friend class core::Host;
			friend class SceneManager;
			friend class SceneController;
		};
	}
}

#endif
