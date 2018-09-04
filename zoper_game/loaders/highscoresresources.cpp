#include "highscoresresources.hpp"
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void HighScoresResources::loadResources(IResourceHandler&resourceHandler)
	{
        constexpr static char BackgroundTextureFile[] = "resources/gr_ms.png";
        constexpr static char MenuFontFile[] = "resources/oldct.ttf";

        resourceHandler.loadTexture(BackgroundTextureId, BackgroundTextureFile);
        resourceHandler.loadFont(MenuFontId, MenuFontFile);
	}
}
