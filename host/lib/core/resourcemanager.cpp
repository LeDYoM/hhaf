#include "resourcemanager.hpp"
#include "log.hpp"
#include "resource.hpp"

namespace lib
{
	namespace core
	{
		ResourceManager::ResourceManager(core::AppController *appController, const std::string &resourceFile)
			: AppService{ appController }, Configuration{ resourceFile }
		{
			if (resourceFile.size() > 0 && !configFileExists(resourceFile))
			{
				throw ResourceNotFoundException(resourceFile);
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
							if (completeId.size() > 1)
							{
								std::string resourceTypeStr = completeId[0];
								std::string id = completeId[1];
								Resource::ResourceType resourceType{ Resource::ResourceType::Empty };
								resourceType = (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F')
									? Resource::ResourceType::Font :
									Resource::ResourceType::Texture;
								resources.push_back(std::make_shared<Resource>(resourceType, resourcesDirectory + dataLine.second, id));
								LOG_DEBUG("Resource with id " << dataLine.second << " from file " << dataLine.first << " added");
							}
							else
							{
								LOG_ERROR("Malformed resource file");
							}
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

		sptr<Resource>& ResourceManager::getResource(const std::string rid)
		{
			for (auto i = 0u; i < resources.size(); ++i)
			{
				if (resources[i]->name() == rid)
				{
					return resources[i];
				}
			}
			throw ResourceNotFoundException(rid);
		}
	}
}
