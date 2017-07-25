#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/properties.hpp>
#include <mtypes/include/str.hpp>
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
		class SceneManager : public AppService
		{
		public:
			SceneManager(core::Window &);
			~SceneManager();

			void addScene(sptr<Scene> newScene);
			void setScene(const str &name);
			void setScene(sptr<Scene> &&scene);

			void addScenes(vector<sptr<Scene>> &&sceneVector);
			sptr<Scene> getSceneByName(const str &name) const;

			void update();

			void finish();

			inline const RenderStatesStack &rStates() const noexcept { return m_renderStates; }
			inline RenderStatesStack &rStates() noexcept { return m_renderStates; }

			ForwardProperty<Rectf32> viewPort;
			ForwardProperty<Rectf32> viewRect;
		private:
			void updateScene();
			friend class core::Host;

			RenderStatesStack m_renderStates;
			vector<sptr<Scene>> m_scenes;
			sptr<Scene> m_currentScene{ nullptr };
			sptr<Scene> m_nextScene{ nullptr };
			core::Window &m_parentWindow;
		};
	}
}

#endif
