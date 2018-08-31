#pragma once

#ifndef ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP
#define ZOOPER_MAINMENU_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/iresourceloader.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
    using namespace lib;

	class MainMenuResources : public IResourceLoader
	{
	public:
        constexpr static char BackgroundTextureId[] = "game_menu.background";
        constexpr static char LogoId[] = "game_menu.logo";
        constexpr static char MenuFontId[] = "menu.mainFont";

		void loadResources(core::ResourceManager&) override;
	};
}

#endif