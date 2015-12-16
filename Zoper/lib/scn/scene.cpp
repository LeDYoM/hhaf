#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"
#include "../core/window.hpp"
#include "draw/renderizable.hpp"

namespace lib
{
	namespace scn
	{
		Scene::Scene(const std::string &_name) : RenderGroup{_name,nullptr}
		{
			LOG_CONSTRUCT("Name: " << name());
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: "<<name());
		}

		void Scene::updateView()
		{
			p_scnManager->parentWindow()->setView(*p_view.get());
			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		sf::View *const Scene::getView() const
		{
			return p_view.get();
		}

		void Scene::privateOnInit()
		{
			LOG_DEBUG("Initializing scene " << name());
			p_view = uptr<sf::View>(new sf::View(p_scnManager->parentWindow()->getView()));
			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
			onInit();
		}

		void Scene::privateOnDeinit()
		{
			LOG_DEBUG("Deinitializing scene " << name());
		}

		void Scene::privateOnEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
			clock.restart();
			onEnterScene();
		}

		void Scene::privateOnExitScene()
		{
			onExitScene();
			LOG_DEBUG("Exited from scene " << name());
		}

		void Scene::onKeyPressed(sf::Event::KeyEvent kEvent)
		{
			LOG_DEBUG("Key pressed: " << int{ kEvent.code });
		}

		void Scene::onKeyReleased(sf::Event::KeyEvent kEvent)
		{
			LOG_DEBUG("Key released: " << int{ kEvent.code });
		}

		void Scene::setNextScene(const std::string &name)
		{
			__ASSERT(p_scnManager, "Null SceneManager on Scene");
			p_scnManager->setScene(name);
		}

		u32 Scene::getRandomNumer(u32 max /*= 1*/, u32 min /*= 0*/)
		{
			return p_scnManager->parentWindow()->getRandomNumer(max, min);
		}

		uptr<ResourceManager> & Scene::resourceManager()
		{
			return p_scnManager->resourceManager();
		}

	}
}
