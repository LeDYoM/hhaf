#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenecontroller.hpp>

#include <lib/core/appservice.hpp>
#include <lib/core/window.hpp>
#include <lib/core/rendertarget.hpp>

namespace lib
{
    class IResourceRetriever;

	namespace core
	{
		class Host;
		class Window;
	}
	namespace scene
	{
		class SceneManager : public AppService
		{
		public:
			SceneManager(core::Host& host, core::Window &window);
			~SceneManager();

			void start();
			void update();
			void finish();

            IResourceRetriever &resources();

            Rectf32 viewPort() const noexcept;
            void setViewPort(const Rectf32& vp) noexcept;
            Rectf32 viewRect() const noexcept;
            void setViewRect(const Rectf32& vr) noexcept;

			inline const sptr<SceneController> &sceneController() const
				noexcept { return scene_controller_; }

			inline sptr<SceneController> &sceneController() 
				noexcept { return scene_controller_; }

		private:
			ComponentContainer m_componentContainer;
			sptr<SceneController> scene_controller_;
			SceneDirectorType scene_director_;
			core::Window &m_parentWindow;
		};
	}
}

#endif
