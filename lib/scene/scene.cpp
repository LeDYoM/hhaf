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
		Scene::Scene(str name) : SceneNode{ nullptr,std::move(name) },
			viewPort{ dynamic_cast<IProperty<Rectf32>*>(&(host().parentWindow().viewPort)) },
			viewRect{ dynamic_cast<IProperty<Rectf32>*>(&(host().parentWindow().viewRect)) }
		{
			logConstruct("Name: ", core::HasName::name());
		}

		Scene::~Scene()
		{
			logDestruct("Name: ", name());
		}

		vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ getCenterCoordinates().x - (coordinates.width / 2.0f), getCenterCoordinates().y - (coordinates.height / 2.0f) };
		}

		vector2df Scene::getCenterCoordinates() const
		{
			return viewRect().center();
		}

		void Scene::onInit()
		{
			log_debug_info("Initializing scene ", name());
			auto sceneSize = getDefaultSizeView();
			viewRect = Rectf32::fromSize(sceneSize);

			log_debug_info("Scene view set to:", viewRect());
		}

		void Scene::onDeinit()
		{
			log_debug_info("Deinitializing scene ", name());
		}

		void Scene::onEnterScene()
		{
			using namespace events;
			log_debug_info("Entered in scene ", name());

			auto sceneSize = getDefaultSizeView();
			viewRect = Rectf32::fromSize(sceneSize);
			log_debug_info("Scene view set to:", viewRect());

			clock.restart();
		}

		void Scene::onExitScene()
		{
			eventConnector.unsubscribeAll();
			log_debug_info("Exited from scene ", name());
		}
	}
}
