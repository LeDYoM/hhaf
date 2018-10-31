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

		SceneDirectorType m_sceneDirector;
		SceneManager* scene_manager_{ nullptr };
	};
}

#endif
