#include "resourcemanager.hpp"
#include "log.hpp"

#include <lib/draw/font.hpp>
#include <lib/draw/texturev1.hpp>
#include <map>

namespace lib
{
	namespace core
	{
		struct ResourceManager::ResourceManagerPrivate
		{
			std::map<str,sptr<IResourceLoader>> loaders;
		};
		ResourceManager::ResourceManager()
			: AppService{ }, m_private{ muptr<ResourceManagerPrivate>() } {}

		ResourceManager::~ResourceManager() = default;

		bool ResourceManager::registerResourceLoader(str name, sptr<IResourceLoader> rlClass)
		{
			auto iterator = m_private->loaders.find(name);
			if (iterator != m_private->loaders.end()) {
				m_private->loaders.insert({ std::move(name), std::move(rlClass) });
				return true;
			}
			return false;
		}
	}
}
