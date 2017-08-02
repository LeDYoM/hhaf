#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <lib/include/properties.hpp>
#include <lib/core/appservice.hpp>
#include "renderstatesstack.hpp"

namespace lib
{
	namespace core
	{
		class Host;
		class Window;
	}
	namespace scene
	{
		class Scene;
		class IScenesController;
		class SceneManager : public AppService
		{
		public:
			SceneManager(core::Window &);
			~SceneManager();

			void setScenesController(uptr<IScenesController> scenesController);

			void setScene(sptr<Scene> scene);
			void terminateScene();

			void update();

			void finish();

			inline const RenderStatesStack &rStates() const noexcept { return m_renderStates; }
			inline RenderStatesStack &rStates() noexcept { return m_renderStates; }

			ForwardProperty<Rectf32> viewPort;
			ForwardProperty<Rectf32> viewRect;
		private:
			RenderStatesStack m_renderStates;
			sptr<Scene> m_currentScene{ nullptr };
			sptr<Scene> m_nextScene{ nullptr };
			core::Window &m_parentWindow;
			uptr<IScenesController> m_scenesController;
		};
	}
}

#endif
