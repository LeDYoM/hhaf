#include "mainmenuresources.hpp"

#include <lib/include/resources/iresourcehandler.hpp>

#include <lib/resources/texture.hpp>
#include <lib/resources/ttfont.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;

	void MainMenuResources::loadResources(IResourceHandler&resourceHandler)
	{
        constexpr static char BackgroundTextureFile[] = "resources/gr_ms.png";
        constexpr static char LogoFile[] = "resources/zoperbl.png";
        constexpr static char MenuFontFile[] = "resources/oldct.ttf";
//        constexpr static char MenuFontFile[] = "lucida";

        resourceHandler.loadTexture(BackgroundTextureId, BackgroundTextureFile);
        resourceHandler.loadTexture(LogoId, LogoFile);
        resourceHandler.loadTTFont(MenuFontId, MenuFontFile);
//        resourceHandler.loadBMPFont(MenuFontId, MenuFontFile);
	}
}
