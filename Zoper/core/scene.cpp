#include "scene.hpp"
#include "log.hpp"

namespace lib
{
	namespace core
	{
		Scene::Scene(const std::string &name) : HasName(name)
		{
		}


		Scene::~Scene()
		{
		}

		void Scene::onEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
		}

		void Scene::onExitScene()
		{
			LOG_DEBUG("Exited from scene " << name());
		}

	}
}
