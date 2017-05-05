#include "resourcemanager.hpp"
#include "log.hpp"

#include <lib/draw/ttfont.hpp>
#include <lib/draw/texture.hpp>

#include <algorithm>

namespace lib
{
	namespace core
	{
		namespace
		{
			template <typename T>
			inline void add(ResourceManager::ResourceList<sptr<T>> &container, const std::string &id, const std::string &fileName)
			{
				auto&& resource(msptr<T>());
				resource->loadFromFile(fileName);
				container.push_back(ResourceManager::NamedIndex<sptr<T>>(id,std::move(resource)));
			}

		}
		ResourceManager::ResourceManager(const std::string &resourceFile)
			: AppService{}, Configuration{ resourceFile }
		{
			using std::string;

			if (resourceFile.size() > 0 && !configFileExists(resourceFile)) {
				__ASSERT("Resource not found: ", resourceFile);
			}
			else
			{
				if (!resourceFile.empty()) {
					static const char *const resourcesDirectoryKey = "resources_directory";
					const auto resourcesDirectory = value(resourcesDirectoryKey)->get<string>();
					for_each_property([&resourcesDirectory, this](const Configuration::CMapLine &dataLine) {
						if (dataLine.first != resourcesDirectoryKey) {
							auto completeId (splitString(dataLine.first, '@'));
							if (completeId.size() > 1) {
								string resourceTypeStr = completeId[0];
								string id = completeId[1];
								string filename(resourcesDirectory + dataLine.second->get<string>());
								if (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F') {
									add(m_fonts, id, filename);
								}
								else {
									add(m_textures, id, filename);

								}
								logDebug("Resource with id ", dataLine.second->get<string>(), " from file ", dataLine.first, " added");
							}
							else {
								logError("Malformed resource file");
							}
						}
					});
				}
				else {
					logDebug("Empty resources file. No resources loaded or used");
				}
			}
		}

		ResourceManager::~ResourceManager() = default;

		sptr<draw::TTFont> ResourceManager::getFont(const str &rid) const
		{
			auto iterator(std::find_if(m_fonts.begin(), m_fonts.end(), 
				[rid](const auto &node) {return node.first == rid; })
			);
			return iterator == m_fonts.end() ? nullptr : (*iterator).second;
		}
		sptr<draw::Texture> ResourceManager::getTexture(const str &rid) const
		{
			auto iterator(std::find_if(m_textures.begin(), m_textures.end(),
				[rid](const auto &node) {return node.first == rid; })
			);
			return iterator == m_textures.end() ? nullptr : (*iterator).second;
		}
	}
}
