#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"
#include "window.hpp"
#include "../stostr.hpp"
#include "../draw/renderizable.hpp"

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

		sf::Text *const Scene::createText(const std::string &name)
		{
			auto result = sptr<lib::draw::Renderizable>(new lib::draw::Renderizable(name,new sf::Text));
			v_nodes.push_back(result);
			return result->getAsText();
		}

		sf::Sprite* const Scene::createSprite(const std::string &name)
		{
			auto result = sptr<lib::draw::Renderizable>(new lib::draw::Renderizable(name, new sf::Sprite));
			v_nodes.push_back(result);
			return result->getAsSprite();
		}

		sf::Shape* const Scene::createShape(const std::string &name)
		{
			auto result = sptr<lib::draw::Renderizable>(new lib::draw::Renderizable(name, new sf::CircleShape));
			v_nodes.push_back(result);
			return result->getAsShape();
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
	}
}
