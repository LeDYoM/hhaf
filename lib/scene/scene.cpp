#include "scene.hpp"

#include <lib/system/resourcemanager.hpp>

#include <lib/resources/include/iresourceloader.hpp>
#include <lib/resources/include/iresourcehandler.hpp>
#include <lib/system/systemprovider.hpp>

namespace lib::scene
{
	Scene::Scene(str name) : SceneNode{ nullptr,std::move(name) } {}

	Scene::~Scene() = default;
}
