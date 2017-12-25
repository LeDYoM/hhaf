#include "scene.hpp"
#include "renderizable.hpp"
#include <mtypes/include/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace scene
	{
		Scene::Scene(str name) : SceneNode{ nullptr,std::move(name) } {}

		Scene::~Scene()
		{
			eventConnector.unsubscribeAll();
		}

		void Scene::onCreated()
		{
			using namespace events;
			clock.restart();
		}
	}
}
