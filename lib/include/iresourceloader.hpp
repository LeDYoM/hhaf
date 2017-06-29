#pragma once

#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

#include <mtypes/include/str.hpp>

namespace lib
{
	struct ResourceForLoading
	{
		const str name;
	};
	class IResourceLoader {
	public:
		virtual void loadResources() = 0;
	};
}

#endif
