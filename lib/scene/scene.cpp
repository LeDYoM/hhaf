#include "scene.hpp"

#include <lib/system/resourcemanager.hpp>
#include <lib/scene/scenemanager.hpp>

#include <lib/include/resources/iresourceloader.hpp>
#include <lib/include/resources/iresourcehandler.hpp>

namespace lib::scene
{
	Scene::Scene(str name) : SceneNode{ nullptr,std::move(name) } {}

	Scene::~Scene() = default;

    void Scene::loadResources(IResourceLoader&& resourceLoader)
    {
        resourceLoader.loadResources(sceneManager().systemProvider().resourceManager());
    }
}
