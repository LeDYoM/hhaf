#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <lib/include/properties.hpp>
#include <lib/core/appservice.hpp>
#include <lib/core/window.hpp>

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

			inline const Rectf32 &viewPort() const noexcept { return m_parentWindow.viewPort(); }
			inline void setViewPort(Rectf32 vp) noexcept { m_parentWindow.viewPort = std::move(vp); }
			inline const Rectf32 &viewRect() const noexcept { return m_parentWindow.viewRect(); }
			inline void setViewRect(Rectf32 vr) noexcept { m_parentWindow.viewRect = std::move(vr); }

		private:
			sptr<Scene> m_currentScene{ nullptr };
			sptr<Scene> m_nextScene{ nullptr };
			core::Window &m_parentWindow;
			uptr<IScenesController> m_scenesController;
		};
	}
}

#endif
