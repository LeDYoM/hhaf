#include "scene.hpp"
#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/events/eventmanager.hpp>
#include <lib/core/events/inputevent.hpp>

namespace lib
{
	namespace draw
	{
		Scene::Scene(const std::string &_name) : RenderGroup{ _name,nullptr }
		{
			logConstruct("Name: ", name());
		}

		Scene::~Scene()
		{
			logDestruct("Name: ", name());
		}

		void Scene::updateView()
		{
			core::Host::host().parentWindow().setView(p_view->externalView());
			logDebug("Scene view set to: center: ", p_view->perspective().center(), " and size: ", p_view->perspective().size());
		}

		const uptr<View> &Scene::getView() const
		{
			return p_view;
		}

		vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ getCenterCoordinates().x - (coordinates.width / 2.0f), getCenterCoordinates().y - (coordinates.height / 2.0f) };
		}

		vector2df Scene::getCenterCoordinates() const
		{
			return p_view->perspective().center();
		}

		void Scene::onInit()
		{
			logDebug("Initializing scene ", name());
			p_view = std::make_unique<View>(core::Host::host().parentWindow().getView());
			auto sceneSize = getDefaultSizeView();
			p_view->perspective.set({ 0,0,sceneSize.x, sceneSize.y });
			updateView();

			logDebug("Scene view set to: center: ", p_view->perspective().center(), " and size: ", p_view->perspective().size());
		}

		void Scene::onDeinit()
		{
			logDebug("Deinitializing scene ", name());
		}

		void Scene::onEnterScene()
		{
			using namespace events;
			logDebug("Entered in scene ", name());
			eventConnector.addSubscription(KeyPressedEvent::subscribe([this](const Event&) {
				logDebug("Key pressed from Scene: ", name());
			}));

			auto sceneSize = getDefaultSizeView();
			p_view->perspective.set({ 0,0,sceneSize.x, sceneSize.y });
			updateView();

			logDebug("Scene view set to: center: ", p_view->perspective().center(), " and size: ", p_view->perspective().size());

			clock.restart();
		}

		void Scene::onExitScene()
		{
			eventConnector.unsubscribeAll();
			logDebug("Exited from scene ", name());
		}
	}
}
