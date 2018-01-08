#include "mainmenuresources.hpp"
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void MainMenuResources::loadResources(core::ResourceManager&resourceManager)
	{
		background = resourceManager.getResource<Texture>("game_menu.background","resources/gr_ms.png");
		logo = resourceManager.getResource<Texture>("game_menu.logo","resources/zoperbl.png");
	}
}
