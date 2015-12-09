#include "resourcemanager.hpp"
#include "../log.hpp"
#include "resource.hpp"

namespace lib
{
	namespace scn
	{
		ResourceManager::ResourceManager(const std::string &resourceFile)
			: Configuration{ resourceFile }
		{
			if (resourceFile.size() > 0 && !configFileExists(resourceFile))
			{
				LOG_ERROR("Error: Resource definition file " << resourceFile << " does not exists");
			}
			else
			{
				if (resourceFile.size() > 0)
				{
					for_each_property([](const Configuration::CMapLine &dataLine) 
					{
						Resource *a = new Resource(Resource::ResourceType::Font, dataLine.second, dataLine.first);
						uptr<Resource> resource = std::make_unique<Resource>(Resource::ResourceType::Font, dataLine.second, dataLine.first);
						LOG_DEBUG("Resource with id " << dataLine.second << " from file " << dataLine.first << " added");
					});
				}
				else
				{
					LOG_DEBUG("Empty resources file. No resources loaded or used");
				}
			}
		}


		ResourceManager::~ResourceManager()
		{
			resources.clear();
		}

		uptr<Resource>& ResourceManager::getResource(const std::string &rid)
		{
			return resources[rid];
		}
	}
}
