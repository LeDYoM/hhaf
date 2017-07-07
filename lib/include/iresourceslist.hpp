#pragma once

#ifndef LIB_IRESOURCESLIST_INCLUDE_HPP
#define LIB_IRESOURCESLIST_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <lib/core/iuserproperties.hpp>
#include <lib/core/resourceloader.hpp>

namespace lib
{
	class IResourcesList : public IUserProperties {
	public:
		virtual void loadResources(core::ResourceLoader &resourceLoader) = 0;
	};
}

#endif
