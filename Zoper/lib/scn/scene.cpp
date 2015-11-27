#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"
#include "../core/window.hpp"
#include "draw/renderizable.hpp"

namespace lib
{
	namespace scn
	{
		Scene::Scene(const std::string &_name) : HasName{ _name }
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

		sptr<draw::Renderizable> Scene::createText(const std::string &name)
		{
			auto result = sptr<draw::Renderizable>(new draw::Renderizable(name,new sf::Text));
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> Scene::createSprite(const std::string &name)
		{
			auto result = sptr<draw::Renderizable>(new draw::Renderizable(name, new sf::Sprite));
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> Scene::createShape(const std::string &name)
		{
			auto result = sptr<draw::Renderizable>(new draw::Renderizable(name, new sf::CircleShape));
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> Scene::addRenderizable(sptr<draw::Renderizable> newElement)
		{
			v_nodes.push_back(newElement);
			return newElement;
		}

		u32 Scene::drawAll()
		{
			auto window = p_scnManager->parentWindow();

			u32 rNodes{ 0 };
			
			for (auto renderizable : v_nodes)
			{
				window->draw(*(renderizable->getAsDrawable()));
				++rNodes;
			}
			return rNodes;
		}

		u32 Scene::getRandomNumer(u32 max /*= 1*/, u32 min /*= 0*/)
		{
			return p_scnManager->parentWindow()->getRandomNumer(max, min);
		}

	}
}