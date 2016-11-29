#include "resourcemanager.hpp"
#include "log.hpp"

#include <lib/draw/font.hpp>
#include <lib/draw/texture.hpp>

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
								if (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F') {
									sptr<draw::Font> font = sptr<draw::Font>(new draw::Font());

									m_fonts.emplace_back(msptr<draw::Font>(resourceType, resourcesDirectory + dataLine.second->get<string>(), id));
								} else {
									m_textures.emplace_back(msptr<Resource>(resourceType, resourcesDirectory + dataLine.second->get<string>(), id));
								}
								logDebug("Resource with id ", dataLine.second, " from file ", dataLine.first, " added");
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

		sptr<draw::Font> ResourceManager::getFont(const std::string rid) const
		{
			auto iterator(std::find_if(m_fonts.begin(), m_fonts.end(), [&rid](const sptr<draw::Font> &font) {return font->name() == rid; }));
			return iterator == m_fonts.end() ? nullptr : *iterator;
		}
		sptr<draw::Texture> ResourceManager::getTexture(const std::string rid) const
		{
			auto iterator(std::find_if(m_textures.begin(), m_textures.end(), [&rid](const sptr<draw::Texture> &texture) {return texture->name() == rid; }));
			return iterator == m_textures.end() ? nullptr : *iterator;
		}
	}
}
