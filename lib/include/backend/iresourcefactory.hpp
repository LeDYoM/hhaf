#pragma once

#ifndef LIB_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define LIB_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <mtypes/include/str.hpp>

namespace lib::backend
{
    template <typename T>
	class IResourceFactory
	{
	public:
		virtual T* loadFromFile(const str &file) = 0;
		virtual ~IResourceFactory() {}
	};
}
#endif
