#include "scenemanager.hpp"
#include "scene.hpp"

#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/include/core/log.hpp>

#include <lib/include/resources/iresourceretriever.hpp>

namespace lib::scene
{
	SceneManager::SceneManager(core::Host& host, core::Window &window) 
        : AppService{ host }, m_parentWindow { window } {}

	SceneManager::~SceneManager() = default;

	void SceneManager::start()
	{
        m_statesController = m_componentContainer.ensureComponentOfType<StatesController<sptr<Scene>>>();
	}

	void SceneManager::terminateScene()
	{
        log_debug_info("Terminating scene ", m_statesController->currentState()->name());
        assert_debug(m_statesController != nullptr, "terminateScene with no current scene");
        sptr<Scene> nextScene;
		if (m_sceneDirector)
        {
			nextScene = m_sceneDirector(m_statesController->currentState());
		}

        log_debug_info("Setting new scene: ", nextScene?nextScene->name():"<nullptr>");
		m_statesController->setState(std::move(nextScene));
	}

	void SceneManager::setSceneDirector(SceneDirectorType sceneDirector)
	{
		m_sceneDirector = std::move(sceneDirector);
	}

	void SceneManager::update()
	{
		m_componentContainer.updateComponents();

        if (auto&& currentScene = m_statesController->currentState()) 
        {
			currentScene->updateScene();
			currentScene->render(false);
		}
	}

	void SceneManager::finish()
	{
		m_statesController->pop_state();
	}

    IResourceRetriever & SceneManager::resources()
    {
        return host().resourceManager();
    }

    void SceneManager::startScene(sptr<Scene> scene)
    {
        scene->m_sceneManager = this;
        scene->onCreated();
    }
}
