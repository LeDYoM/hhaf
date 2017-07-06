#pragma once

#ifndef LIB_IRESOURCELOADER_INCLUDE_HPP
#define LIB_IRESOURCELOADER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <lib/core/iuserproperties.hpp>
#include <lib/core/resourcemanager.hpp>

namespace lib
{
	class ResourceAddress
	{
	public:
		ResourceAddress(str fileName) : m_fileName{ std::move(fileName) } {}
	private:
		str m_fileName;
	};
	class IResourceLoader : public IUserProperties {
	public:
		virtual void loadResources(core::ResourceManager &resourceManager) = 0;
	};
}

#endif
