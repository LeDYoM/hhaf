#include "resourcemanager.hpp"
#include "log.hpp"
#include "resource.hpp"


namespace lib
{
	namespace core
	{
		ResourceManager::ResourceManager(const std::string &resourceFile)
			: AppService{ }, Configuration{ resourceFile }
		{
			using std::string;

			if (resourceFile.size() > 0 && !configFileExists(resourceFile)) {
				throw ResourceNotFoundException(resourceFile);
			}
			else
			{
				if (!resourceFile.empty()) {
					static const char *const resourcesDirectoryKey = "resources_directory";
					const auto resourcesDirectory = value(resourcesDirectoryKey)->get<string>();
					for_each_property([&resourcesDirectory,this](const Configuration::CMapLine &dataLine) {
						if (dataLine.first != resourcesDirectoryKey) {
							auto completeId = splitString(dataLine.first, '@');
							if (completeId.size() > 1) {
								string resourceTypeStr = completeId[0];
								string id = completeId[1];
								Resource::ResourceType resourceType{ Resource::ResourceType::Empty };
								resourceType = (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F')
									? Resource::ResourceType::Font :
									Resource::ResourceType::Texture;
								resources.emplace_back(msptr<Resource>(resourceType, resourcesDirectory + dataLine.second->get<string>(), id));
								LOG_DEBUG("Resource with id " << dataLine.second << " from file " << dataLine.first << " added");
							}
							else {
								LOG_ERROR("Malformed resource file");
							}
						}
					});
				}
				else {
					LOG_DEBUG("Empty resources file. No resources loaded or used");
				}
			}
		}

		ResourceManager::~ResourceManager() = default;

		sptr<Resource>& ResourceManager::getResource(const std::string rid)
		{
			for (auto i = 0u; i < resources.size(); ++i) {
				if (resources[i]->name() == rid) {
					return resources[i];
				}
			}
			throw ResourceNotFoundException(rid);
		}
	}
}
