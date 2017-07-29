#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <lib/include/properties.hpp>
#include <lib/core/appservice.hpp>
#include <lib/core/factory.hpp>
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

			template <typename T>
			constexpr void addSceneType()
			{
				m_sceneFactory.registerSingletonType<T>();
			}

			template <typename T>
			constexpr void setCurrentSceneType()
			{
				setScene(m_sceneFactory.getSingletonInterface<T>());
			}

			void addScene(sptr<Scene> newScene);
			void setScene(sptr<Scene> scene);
			void terminateScene();

			void addScenes(vector<sptr<Scene>> &&sceneVector);
			sptr<Scene> getSceneByName(const str &name) const;

			void update();

			void finish();

			inline const RenderStatesStack &rStates() const noexcept { return m_renderStates; }
			inline RenderStatesStack &rStates() noexcept { return m_renderStates; }

			ForwardProperty<Rectf32> viewPort;
			ForwardProperty<Rectf32> viewRect;
		private:

			FactoryOfSingletons<Scene> m_sceneFactory;
			void updateScene();
			friend class core::Host;

			RenderStatesStack m_renderStates;
			vector<sptr<Scene>> m_scenes;
			sptr<Scene> m_currentScene{ nullptr };
			sptr<Scene> m_nextScene{ nullptr };
			core::Window &m_parentWindow;
			uptr<IScenesController> m_scenesController;
		};
	}
}

#endif
