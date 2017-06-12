#ifndef ZOOPER_GAME_RESOURCES_INCLUDE_HPP
#define ZOOPER_GAME_RESOURCES_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>
#include <lib/include/logcl.hpp>
#include <lib/include/iresourceloader.hpp>

namespace zoper
{
	class GameResourcesLoader : public lib::IResourceLoader
	{
	public:
		virtual void loadResources() override;
	};
}

#endif