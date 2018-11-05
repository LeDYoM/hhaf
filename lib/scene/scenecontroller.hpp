#pragma once

#ifndef LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/scene.hpp>

namespace lib::scene
{
	using SceneDirectorType = function<sptr<Scene>(sptr<Scene>)>;
	class SceneManager;

	class SceneController : public StatesController<sptr<Scene>>
	{
	private:
		using BaseClass = StatesController<sptr<Scene>>;
	public:

		void setSceneManager(SceneManager *scene_manager);
	
		void terminateScene();
		void setSceneDirector(SceneDirectorType sceneDirector);
		void update();
		void finish();

		template <typename T>
		void startFirstScene()
		{
			auto scene( createScene<T>() );
			startScene(std::move(scene));
		}

		template <typename T>
		sptr<T> createScene() {
			auto scene(msptr<T>());
			return std::dynamic_pointer_cast<T>(scene);
		}


	private:
		void startScene(sptr<Scene> scene);

		SceneDirectorType m_sceneDirector;
		SceneManager* scene_manager_{ nullptr };
	};
}

#endif
