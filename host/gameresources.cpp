#include "gameresources.hpp"
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void GameResourcesLoader::loadResources(core::ResourceManager&resourceManager)
	{
		scoreFont = resourceManager.getResource<TTFont>("game_scene.scoreFont");
	}
}
