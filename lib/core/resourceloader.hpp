#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#pragma once

#include <mtypes/include/types.hpp>
#include <lib/include/iresourceloader.hpp>

namespace lib
{
	namespace core
	{
		class ResourceLoader
		{
		public:
			ResourceLoader();
			~ResourceLoader();

		private:
			struct ResourceLoaderPrivate;
			uptr<ResourceLoaderPrivate> m_private;
		};
	}
}

#endif
