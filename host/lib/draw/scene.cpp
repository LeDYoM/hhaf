#include "scene.hpp"
#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/eventmanager.hpp>
#include <lib/include/events/inputevent.hpp>

namespace lib
{
	namespace scn
	{
		Scene::Scene(const std::string &_name) : RenderGroup{_name,nullptr}
		{
			using namespace events;

			LOG_CONSTRUCT("Name: " << name());
			eventConnector.addSubscription(KeyPressedEvent::subscribe([this](const Event&) {
				LOG_DEBUG("Key pressed from Scene: "<< name());
			}));
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: "<<name());
		}

		void Scene::updateView()
		{
			core::Host::host().parentWindow().setView(*p_view.get());
			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		sf::View *const Scene::getView() const
		{
			return p_view.get();
		}

		const vector2df Scene::getCoordinatesToCenter(const sf::FloatRect &coordinates) const
		{
			return{ getCenterCoordinates().x - (coordinates.width / 2.0f), getCenterCoordinates().y - (coordinates.height / 2.0f) };
		}

		const vector2df Scene::getCenterCoordinates() const
		{
			return{ p_view->getSize().x / 2.0f, p_view->getSize().y / 2.0f };
		}

		void Scene::onInit()
		{
			LOG_DEBUG("Initializing scene " << name());
			p_view = uptr<sf::View>(new sf::View(core::Host::host().parentWindow().getView()));
			auto sceneSize = getDefaultSizeView();
			p_view->setSize(sceneSize.x, sceneSize.y);
			p_view->setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		void Scene::onDeinit()
		{
			LOG_DEBUG("Deinitializing scene " << name());
		}

		void Scene::onEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
			auto sceneSize = getDefaultSizeView();
			p_view->setSize(sceneSize.x, sceneSize.y);
			p_view->setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);

			clock.restart();
		}

		void Scene::onExitScene()
		{
			eventConnector.unsubscribeAll();
			LOG_DEBUG("Exited from scene " << name());
		}
	}
}
