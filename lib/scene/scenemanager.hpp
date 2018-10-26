#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/scene.hpp>

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
        class Scene;

		using SceneDirectorType = function<sptr<Scene>(sptr<Scene>)>;

		class SceneManager : public AppService
		{
		public:
			SceneManager(core::Host& host, core::Window &window);
			~SceneManager();

			void terminateScene();
			void setSceneDirector(SceneDirectorType sceneDirector);

			void update();

			void finish();

            IResourceRetriever &resources();

            inline Rectf32 viewPort() const noexcept
            {
                return m_parentWindow.renderTarget()->viewPort();
            }

            inline void setViewPort(const Rectf32& vp) noexcept
            {
                m_parentWindow.renderTarget()->setViewPort(vp);
            }

            Rectf32 viewRect() const noexcept
            {
                return m_parentWindow.renderTarget()->viewRect();
            }

            inline void setViewRect(const Rectf32& vr) noexcept
            {
                m_parentWindow.renderTarget()->setViewRect(vr);
            }

			template <typename T>
			void startFirstScene()
			{
                auto scene( createScene<T>() );
                start();
				m_statesController->start(std::move(scene));
			}

			template <typename T>
			sptr<T> createScene() {
				auto scene(msptr<T>());
                startScene(scene);
				return std::dynamic_pointer_cast<T>(scene);
			}


		private:
            void start();
            void startScene(sptr<Scene> scene);
			ComponentContainer m_componentContainer;
			sptr<StatesController<sptr<Scene>>> m_statesController;
			SceneDirectorType m_sceneDirector;
			core::Window &m_parentWindow;
		};
	}
}

#endif
