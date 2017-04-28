#include "resourceloader.hpp"
#include "log.hpp"

#include <map>

namespace lib
{
	namespace core
	{
		struct ResourceLoader::ResourceLoaderPrivate
		{
			std::map<str,sptr<IResourceLoader>> loaders;
		};
		ResourceLoader::ResourceLoader() : m_private{ muptr<ResourceLoaderPrivate>() } {}

		ResourceLoader::~ResourceLoader() = default;

	}
}
