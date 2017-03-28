#include "scene.hpp"
#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/events/eventmanager.hpp>

namespace lib
{
	namespace draw
	{
		Scene::Scene(str_const name) : SceneNode{ nullptr,std::move(name) },
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
			logDebug("Initializing scene ", name());
//			p_view = std::make_unique<View>(core::Host::host().parentWindow().getView());
			auto sceneSize = getDefaultSizeView();
//			p_view->perspective.set({ 0,0,sceneSize.x, sceneSize.y });
//			updateView();
			viewRect = Rectf32::fromSize(sceneSize);

			logDebug("Scene view set to:", viewRect());
		}

		void Scene::onDeinit()
		{
			logDebug("Deinitializing scene ", name());
		}

		void Scene::onEnterScene()
		{
			using namespace events;
			logDebug("Entered in scene ", name());

			auto sceneSize = getDefaultSizeView();
			viewRect = Rectf32::fromSize(sceneSize);
			logDebug("Scene view set to:", viewRect());

			clock.restart();
		}

		void Scene::onExitScene()
		{
			eventConnector.unsubscribeAll();
			logDebug("Exited from scene ", name());
		}
	}
}
