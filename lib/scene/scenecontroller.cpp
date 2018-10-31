#include "scenecontroller.hpp"
#include "scenemanager.hpp"
#include "scene.hpp"

#include <lib/include/core/log.hpp>


namespace lib::scene
{
	void SceneController::setSceneManager(SceneManager *scene_manager)
	{
		scene_manager_ = scene_manager;
	}

	void SceneController::start()
	{
	}

	void SceneController::terminateScene()
	{
        log_debug_info("Terminating scene ", this->currentState()->name());
        sptr<Scene> nextScene;
		if (m_sceneDirector)
        {
			nextScene = m_sceneDirector(currentState());
		}

        log_debug_info("Setting new scene: ", nextScene?nextScene->name():"<nullptr>");
		this->setState(std::move(nextScene));
	}

	void SceneController::setSceneDirector(SceneDirectorType sceneDirector)
	{
		m_sceneDirector = std::move(sceneDirector);
	}

	void SceneController::update()
	{
        if (auto&& currentScene = this->currentState()) 
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
        scene->onCreated();
    }
}
