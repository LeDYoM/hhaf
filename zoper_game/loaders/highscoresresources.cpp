#include "highscoresresources.hpp"
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void HighScoresResources::loadResources(core::ResourceManager&resourceManager)
	{
        constexpr static char BackgroundTextureFile[] = "resources/gr_ms.png";
        constexpr static char MenuFontFile[] = "resources/oldct.ttf";

        resourceManager.loadTexture(BackgroundTextureId, BackgroundTextureFile);
        resourceManager.loadFont(MenuFontId, MenuFontFile);
	}
}
