#pragma once

#ifndef LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP
#define LIB_SCENE_SCENECONTROLLER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>

#include <lib/scene/components/statescontroller.hpp>
#include <lib/scene/components/icomponent.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenefactory.hpp>

namespace lib::scene
{
	using SceneDirectorType = function<str(const str&)>;
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

        sptr<Scene> currentScene();
        bool currentSceneIsNull();

		bool startScene(const str &sceneName);

		template <typename T>
		bool registerAndStartScene(const str &sceneName)
		{
			if (scene_factory_.registerSceneType<T>(sceneName))
			{
				return startScene(sceneName);
			}
			return false;
		}

		template <typename T>
		bool registerAndStartScene()
		{
			if (sceneFactory_.registerSceneType<T>())
			{
				return startScene(sceneName);
			}
			return false;
		}

		template <typename T>
		bool registerSceneType()
		{
			return scene_factory_.registerSceneType<T>();
		}

		template <typename T> 
		inline bool startScene()
		{
			return startScene(T::StaticTypeName);
		}

		inline SceneFactory& sceneFactory() noexcept { return scene_factory_; }
		inline const SceneFactory& sceneFactory() const noexcept { return scene_factory_; }

	private:
		void startScene(sptr<Scene> scene);

		SceneDirectorType scene_director_;
		SceneFactory scene_factory_;
		SceneManager* scene_manager_{ nullptr };
	};
}

#endif
