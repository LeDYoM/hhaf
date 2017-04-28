#ifndef LIB_RESOURCEMANAGER_INCLUDE_HPP__
#define LIB_RESOURCEMANAGER_INCLUDE_HPP__

#pragma once

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <lib/include/iresourceloader.hpp>

namespace lib
{
	namespace core
	{
		class ResourceManager : public AppService
		{
		public:
			ResourceManager();
			~ResourceManager();

			bool registerResourceLoader(str name, sptr<IResourceLoader> rlClass);
		private:
			struct ResourceManagerPrivate;
			uptr<ResourceManagerPrivate> m_private;
		};
	}
}

#endif
