#include "scene.hpp"
#include <lib/scene/renderizables/renderizable.hpp>

#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/scene/scenemanager.hpp>

#include <lib/include/core/log.hpp>
#include <lib/include/resources/iresourceloader.hpp>
#include <lib/include/resources/iresourcehandler.hpp>

#include <type_traits>

namespace lib::scene
{
	Scene::Scene(str name) : SceneNode{ nullptr,std::move(name) } {}

	Scene::~Scene() = default;

	void Scene::onCreated()
	{
        m_sceneStates = ensureComponentOfType<std::remove_reference_t<decltype(*m_sceneStates)>>();
		m_sceneStates->start(0);
    }

    size_type Scene::state()
    {
        return m_sceneStates->currentState();
    }

    void Scene::setState(const size_type ns)
    {
        m_sceneStates->setState(ns);
    }

    void Scene::loadResources(IResourceLoader&& resourceLoader)
    {
        resourceLoader.loadResources(sceneManager().systemProvider().resourceManager());
    }
}
