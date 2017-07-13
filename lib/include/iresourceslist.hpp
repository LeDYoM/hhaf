#pragma once

#ifndef LIB_IRESOURCESLIST_INCLUDE_HPP
#define LIB_IRESOURCESLIST_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <lib/core/resourceloader.hpp>

namespace lib
{
	class IResourcesList {
	public:
		virtual void registerResources(core::ResourceLoader &resourceLoader) = 0;
		virtual void aquireResources(core::ResourceLoader &resourceLoader) = 0;
	};
}

#endif
