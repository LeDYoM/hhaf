#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"
#include "window.hpp"
#include "../stostr.hpp"

namespace lib
{
	namespace core
	{
		wptr<SceneManager> Scene::p_scnManager;

		Scene::Scene(const std::string &name) : HasName(name)
		{
			LOG_CONSTRUCT("Name: "<<name);
			p_view = uptr<sf::View>(new sf::View(p_scnManager.lock()->p_parentWindow.lock()->getView()));
			LOG_DEBUG("Scene view set to: center: " << V2_TOLOG(p_view->getCenter()) << " and size: " << V2_TOLOG(p_view->getSize()));
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: "<<name());
		}

		void Scene::onEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
		}

		void Scene::onExitScene()
		{
			LOG_DEBUG("Exited from scene " << name());
		}

		void Scene::setNextScene(const std::string &name)
		{
			__ASSERT(!p_scnManager.expired(), "Null SceneManager on Scene");
			p_scnManager.lock()->setScene(name);
		}

		void Scene::draw(const sf::Drawable &drawable)
		{
			p_scnManager.lock()->p_parentWindow.lock()->draw(drawable);
		}

		sptr<sf::Text> Scene::createText()
		{

		}

	}
}
