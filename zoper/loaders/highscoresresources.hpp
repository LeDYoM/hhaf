#ifndef ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP
#define ZOOPER_HIGHSCORES_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/include/iresourceloader.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/ttfont.hpp>

namespace zoper
{
	class HighScoresResources : public lib::IResourceLoader
	{
	public:
		virtual void loadResources(lib::core::ResourceManager&) override;

		lib::sptr<lib::scene::Texture> background;
		lib::sptr<lib::scene::TTFont> mainFont;
		
	};
}

#endif