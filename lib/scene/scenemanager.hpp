#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/properties.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/components/statescontroller.hpp>
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
		class SceneManager : public AppService
		{
		public:
			SceneManager(core::Window &);
			~SceneManager();

			void startScene(sptr<Scene> scene);
			void setScene(sptr<Scene> scene);

			void update();

			void finish();

			inline const Rectf32 &viewPort() const noexcept { return m_parentWindow.viewPort(); }
			inline void setViewPort(Rectf32 vp) noexcept { m_parentWindow.viewPort = std::move(vp); }
			inline const Rectf32 &viewRect() const noexcept { return m_parentWindow.viewRect(); }
			inline void setViewRect(Rectf32 vr) noexcept { m_parentWindow.viewRect = std::move(vr); }

		private:
			ComponentContainer m_componentContainer;
			sptr<StatesController<sptr<Scene>>> m_statesController;
			sptr<Scene> m_currentScene{ nullptr };
			sptr<Scene> m_nextScene{ nullptr };
			core::Window &m_parentWindow;
		};
	}
}

#endif
