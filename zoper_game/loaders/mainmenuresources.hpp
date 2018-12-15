#pragma once

#ifndef ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP
#define ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP

#include <lib/include/resources/iresourceloader.hpp>

namespace zoper
{
	class MainMenuResources : public lib::IResourceLoader
	{
	public:
        constexpr static char BackgroundTextureId[] = "game_menu.background";
        constexpr static char LogoId[] = "game_menu.logo";
        constexpr static char MenuFontId[] = "menu.mainFont";

		void loadResources(lib::IResourceHandler&) override;
	};
}

#endif