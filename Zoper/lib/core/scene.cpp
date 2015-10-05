#include "scene.hpp"
#include "../log.hpp"
#include "scenemanager.hpp"

namespace lib
{
	namespace core
	{
		Scene::Scene(const std::string &name) : HasName(name)
		{
			LOG_CONSTRUCT("Name: "<<name);
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
			__ASSERT(p_scnManager, "Null SceneManager on Scene");
			p_scnManager->setScene(name);
		}

	}
}
