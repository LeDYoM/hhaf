#include "resourcemanager.hpp"
#include <mtypes/include/log.hpp>

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
			inline void add(A& factory, ResourceList<sptr<T>> &container, const str &id, const str &fileName)
			{
				sptr<T> resource(msptr<T>(factory.loadFromFile(fileName)));
				container.push_back(NamedIndex<sptr<T>>(id,std::move(resource)));
			}

		}
		ResourceManager::ResourceManager(const str &resourceFile)
			: AppService{}, Configuration{ resourceFile }
		{
			if (!resourceFile.empty()) {
				if (!configFileExists(resourceFile)) {
					__ASSERT("Resource file not found: ", resourceFile);
				} else {
					static const char *const resourcesDirectoryKey = "resources_directory";
					const auto resourcesDirectory = value(resourcesDirectoryKey)->get<str>();
					for_each_property([&resourcesDirectory, this](const Configuration::CMapLine &dataLine) {
						if (dataLine.first.c_str() != resourcesDirectoryKey) {
							auto completeId (dataLine.first.split('@'));
							if (completeId.size() > 1) {
								str resourceTypeStr(completeId[0]);
								str id(completeId[1]);
								str filename(resourcesDirectory + dataLine.second->get<str>());
								if (resourceTypeStr[0] == 'f' || resourceTypeStr[0] == 'F') {
									add(backend::ttfontFactory(), m_fonts, id, filename);
								}
								else {
									add(backend::textureFactory(), m_textures, id, filename);
								}
								log_debug_info("Resource with id ", dataLine.second->get<str>(), " from file ", dataLine.first, " added");
							}
							else {
								log_debug_error("Malformed resource file");
							}
						}
					});
				}
			}
			else {
				log_debug_info("Empty resources file. No resources loaded or used");
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
