#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"
#include "../core/window.hpp"
#include "renderizable.hpp"

namespace lib
{
	namespace scn
	{
		wptr<SceneManager> Scene::p_scnManager;

		Scene::Scene(const std::string &name) : HasName(name)
		{
			LOG_CONSTRUCT("Name: "<<name);
			p_view = uptr<sf::View>(new sf::View(p_scnManager.lock()->p_parentWindow.lock()->getView()));
			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: "<<name());
		}

		void Scene::updateView()
		{
			p_scnManager.lock()->p_parentWindow.lock()->setView(*p_view.get());
			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		sf::View *const Scene::getView() const
		{
			return p_view.get();
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

		sptr<Renderizable> Scene::createText(const std::string &name)
		{
			auto result = sptr<Renderizable>(new Renderizable(name,new sf::Text));
			addRenderizable(result);
			return result;
		}

		sptr<Renderizable> Scene::createSprite(const std::string &name)
		{
			auto result = sptr<Renderizable>(new Renderizable(name, new sf::Sprite));
			addRenderizable(result);
			return result;
		}

		sptr<Renderizable> Scene::createShape(const std::string &name)
		{
			auto result = sptr<Renderizable>(new Renderizable(name, new sf::CircleShape));
			addRenderizable(result);
			return result;
		}

		sptr<Renderizable> Scene::addRenderizable(sptr<Renderizable> newElement)
		{
			v_nodes.push_back(newElement);
			return newElement;
		}

		u32 Scene::drawAll()
		{
			auto window = p_scnManager.lock()->p_parentWindow.lock();

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
			return p_scnManager.lock()->p_parentWindow.lock()->getRandomNumer(max, min);
		}

	}
}
