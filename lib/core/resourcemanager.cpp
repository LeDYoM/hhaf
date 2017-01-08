#include "resourcemanager.hpp"
#include "log.hpp"

#include <lib/draw/font.hpp>
#include <lib/draw/texture.hpp>

namespace lib
{
	namespace core
	{
		namespace
		{
			template <typename T>
			inline void add(std::list<sptr<T>> &container, std::string &&id, std::string &&fileName)
			{
				auto&& resource(msptr<T>(std::move(id)));
				resource->loadFromFile(std::move(fileName));
				container.emplace_back(std::move(resource));
			}

		}
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
								string filename(resourcesDirectory + dataLine.second->get<string>());
								if (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F') {
									add(m_fonts, std::move(id), std::move(filename));
								} else {
									add(m_textures, std::move(id), std::move(filename));

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
