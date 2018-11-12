#include "scenemanager.hpp"
#include "scenecontroller.hpp"
#include "scene.hpp"

#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/include/core/log.hpp>

#include <lib/include/resources/iresourceretriever.hpp>

namespace lib::scene
{
	SceneManager::SceneManager(core::Host& host, core::Window &window) 
        : AppService{ host }, m_parentWindow { window } 
    {
        scene_controller_ = m_componentContainer.ensureComponentOfType<SceneController>();
        scene_controller_->setSceneManager(this);
    }

	SceneManager::~SceneManager() = default;

	void SceneManager::start()
	{
	}

	void SceneManager::update()
	{
		m_componentContainer.updateComponents();
/*
        if (auto&& currentScene = m_statesController->currentState()) 
        {
			currentScene->updateScene();
			currentScene->render(false);
		}
		*/
	}

    void SceneManager::finish()
    {
        scene_controller_->finish();
    }

	Rectf32 SceneManager::viewPort() const noexcept
	{
		return m_parentWindow.renderTarget()->viewPort();
	}

	void SceneManager::setViewPort(const Rectf32& vp) noexcept
	{
		m_parentWindow.renderTarget()->setViewPort(vp);
	}

	Rectf32 SceneManager::viewRect() const noexcept
	{
		return m_parentWindow.renderTarget()->viewRect();
	}

	void SceneManager::setViewRect(const Rectf32& vr) noexcept
	{
		m_parentWindow.renderTarget()->setViewRect(vr);
	}

    IResourceRetriever & SceneManager::resources()
    {
        return host().resourceManager();
    }
}
