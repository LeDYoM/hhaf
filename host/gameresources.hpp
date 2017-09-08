#pragma once

#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/iresourceloader.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	class GameResourcesLoader : public lib::IResourceLoader
	{
	public:
		virtual void loadResources(lib::core::ResourceManager&) override;

		lib::sptr<lib::scene::TTFont> scoreFont;
	};
}

#endif