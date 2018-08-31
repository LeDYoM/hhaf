#pragma once

#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/resources/iresourceloader.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	class GameResources : public lib::IResourceLoader
	{
	public:
        static constexpr char ScoreFontId[] = "game_scene.scoreFont";
		void loadResources(lib::core::ResourceManager&) override;
	};
}

#endif