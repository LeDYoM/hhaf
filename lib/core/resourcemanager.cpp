#include "resourcemanager.hpp"
#include "log.hpp"

#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>
#include <lib/backend/backendfactory.hpp>
#include <algorithm>

namespace lib
{
	namespace core
	{
		namespace
		{
			template <typename T, typename A>
			inline void add(A& factory, ResourceManager::ResourceList<sptr<T>> &container, const std::string &id, const std::string &fileName)
			{
				sptr<T> resource(msptr<T>(factory.loadFromFile(fileName)));
				container.push_back(ResourceManager::NamedIndex<sptr<T>>(id,std::move(resource)));
			}

		}
		ResourceManager::ResourceManager(const std::string &resourceFile)
			: AppService{}, Configuration{ resourceFile }
		{
			using std::string;

			if (!resourceFile.empty()) {
				if (!configFileExists(resourceFile)) {
					__ASSERT("Resource file not found: ", resourceFile);
				}
				else
				{
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
									add(backend::ttfontFactory(), m_fonts, id, filename);
								}
								else {
									add(backend::textureFactory(), m_textures, id, filename);

								}
								logDebug("Resource with id ", dataLine.second->get<string>(), " from file ", dataLine.first, " added");
							}
							else {
								logError("Malformed resource file");
							}
						}
					});
				}
			}
			else {
				logDebug("Empty resources file. No resources loaded or used");
			}
		}

		ResourceManager::~ResourceManager() = default;

		sptr<scene::TTFont> ResourceManager::getFont(const str &rid) const
		{
			auto iterator(std::find_if(m_fonts.begin(), m_fonts.end(), 
				[rid](const auto &node) {return node.first == rid; })
			);
			return iterator == m_fonts.end() ? nullptr : (*iterator).second;
		}
		sptr<scene::Texture> ResourceManager::getTexture(const str &rid) const
		{
			auto iterator(std::find_if(m_textures.begin(), m_textures.end(),
				[rid](const auto &node) {return node.first == rid; })
			);
			return iterator == m_textures.end() ? nullptr : (*iterator).second;
		}
	}
}
