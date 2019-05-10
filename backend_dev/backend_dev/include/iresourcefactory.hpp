#pragma once

#ifndef LIB_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define LIB_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/rawmemory.hpp>

namespace lib::backend
{
    template <typename T>
	class IResourceFactory
	{
	public:
		virtual T* loadFromFile(const str &) = 0;
		virtual T* loadFromRawMemory(RawMemory *) { return nullptr; }
		virtual ~IResourceFactory() {}
	};
}
#endif
