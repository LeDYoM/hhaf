#pragma once

#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <lib/include/iresourceloader.hpp>
#include "iuserproperties.hpp"

namespace lib
{
	namespace core
	{
		class ResourceLoader : IUserProperties
		{
		public:
			ResourceLoader(str fileName);
			~ResourceLoader();

			virtual void loadResources() = 0;
		private:
			struct ResourceLoaderPrivate;
			uptr<ResourceLoaderPrivate> m_private;
		};
	}
}

#endif
