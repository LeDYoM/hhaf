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
			core::Host::host().parentWindow().setView(*p_view.get());
			logDebug("Scene view set to: center: ", p_view->getCenter().x, ",", p_view->getCenter().y, " and size: ", p_view->getSize().x, ",", p_view->getSize().y);
		}

		sf::View *const Scene::getView() const
		{
			return p_view.get();
		}

		vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ getCenterCoordinates().x - (coordinates.width / 2.0f), getCenterCoordinates().y - (coordinates.height / 2.0f) };
		}

		vector2df Scene::getCenterCoordinates() const
		{
			return{ p_view->getSize().x / 2.0f, p_view->getSize().y / 2.0f };
		}

		void Scene::onInit()
		{
			logDebug("Initializing scene ", name());
			p_view = uptr<sf::View>(new sf::View(core::Host::host().parentWindow().getView()));
			auto sceneSize = getDefaultSizeView();
			p_view->setSize(sceneSize.x, sceneSize.y);
			p_view->setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			logDebug("Scene view set to: center: ", p_view->getCenter().x, ",", p_view->getCenter().y, " and size: ", p_view->getSize().x, ",", p_view->getSize().y);
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
			p_view->setSize(sceneSize.x, sceneSize.y);
			p_view->setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			logDebug("Scene view set to: center: ", p_view->getCenter().x, ",", p_view->getCenter().y, " and size: ", p_view->getSize().x, ",", p_view->getSize().y);

			clock.restart();
		}

		void Scene::onExitScene()
		{
			eventConnector.unsubscribeAll();
			logDebug("Exited from scene ", name());
		}
	}
}
