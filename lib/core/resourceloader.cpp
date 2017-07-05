#include "resourceloader.hpp"
#include <mtypes/include/log.hpp>

#include <map>

namespace lib
{
	namespace core
	{
		struct ResourceLoader::ResourceLoaderPrivate
		{
			std::map<str,sptr<IResourceLoader>> loaders;
		};
		ResourceLoader::ResourceLoader(str fileName) : m_private{ muptr<ResourceLoaderPrivate>() }, IUserProperties{ std::move(fileName) } {}

		ResourceLoader::~ResourceLoader() = default;

	}
}
