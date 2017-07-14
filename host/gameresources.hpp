#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/log.hpp>
#include <lib/include/iresourceslist.hpp>
#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>

namespace zoper
{
	class GameResourcesLoader : public lib::IResourcesList
	{
	public:
		void registerResources(lib::core::ResourceLoader &resourceManager) override;
		void aquireResources(lib::core::ResourceLoader &resourceLoader) override;

		lib::sptr<lib::scene::TTFont> m_scoreFont;
	};
}

#endif