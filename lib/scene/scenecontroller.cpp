#include "scenecontroller.hpp"
#include "scenemanager.hpp"
#include "scene.hpp"

#include <lib/include/core/log.hpp>


namespace lib::scene
{
	void SceneController::setSceneManager(SceneManager *scene_manager)
	{
		assert_debug(scene_manager_ == nullptr, "The scene_manager_ was set already");
		scene_manager_ = scene_manager;
	}

	bool SceneController::startScene(const str &sceneName)
	{
		auto scene = scene_factory_.create(sceneName);
		startScene(sptr<Scene>(std::move(scene)));
		return true;
	}

	void SceneController::terminateScene()
	{
        log_debug_info("Terminating scene ", this->currentState()->name());
        sptr<Scene> nextScene;
		if (scene_director_)
        {
			nextScene = scene_factory_.create(scene_director_(currentState()->name()));
		}

        log_debug_info("Setting new scene: ", nextScene ? nextScene->name():"<nullptr>");
        startScene(std::move(nextScene));
	}

	void SceneController::setSceneDirector(SceneDirectorType sceneDirector)
	{
		scene_director_ = std::move(sceneDirector);
	}

	void SceneController::update()
	{
		BaseClass::update();
        if (auto&& currentScene = BaseClass::currentState()) 
        {
			currentScene->updateScene();
			currentScene->render(false);
		}
	}

	void SceneController::finish()
	{
		this->pop_state();
	}

    void SceneController::startScene(sptr<Scene> scene)
    {
        scene->m_sceneManager = scene_manager_;

		this->StateFinished.connect([](const sptr<Scene>& scene) 
		{
			scene->onFinished();
		});

        scene->onCreated();
		BaseClass::start(std::move(scene));
    }
}
