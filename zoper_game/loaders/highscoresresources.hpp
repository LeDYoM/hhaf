#pragma once

#ifndef ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP
#define ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/iresourceloader.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	class HighScoresResources : public lib::IResourceLoader
	{
	public:
        constexpr static char BackgroundTextureId[] = "game_menu.background";
        constexpr static char MenuFontId[] = "highScores.mainFont";

		void loadResources(lib::core::ResourceManager&) override;		
	};
}

#endif