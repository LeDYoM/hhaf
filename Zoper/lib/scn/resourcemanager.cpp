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
					const std::string resourcesDirectoryKey = "resources_directory";
					std::string resourcesDirectory = getAsString(resourcesDirectoryKey);
					for_each_property([&resourcesDirectoryKey,&resourcesDirectory,this](const Configuration::CMapLine &dataLine) 
					{
						if (dataLine.first != resourcesDirectoryKey)
						{
							auto completeId = splitString(dataLine.first, '@');
							std::string resourceTypeStr = completeId[0];
							std::string id = completeId[1];
							Resource::ResourceType resourceType{ Resource::ResourceType::Empty };
							resourceType = (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F')
								? Resource::ResourceType::Font :
								Resource::ResourceType::Texture;
							uptr<Resource> resource = std::make_unique<Resource>(resourceType, resourcesDirectory + dataLine.second, id);
							LOG_DEBUG("Resource with id " << dataLine.second << " from file " << dataLine.first << " added");
						}
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
