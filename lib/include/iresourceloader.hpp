#pragma once

#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

#include <mtypes/include/str.hpp>

namespace lib
{
	namespace core
	{
		class ResourceManager;
	}

	class IResourceLoader {
	public:
		virtual void loadResources(core::ResourceManager&) = 0;
	};
}

#endif
