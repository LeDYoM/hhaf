#pragma once

#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <lib/core/iuserproperties.hpp>

namespace lib
{
	class IResourceLoader : public IUserProperties {
	public:
		virtual void loadResources() = 0;
	};
}

#endif
