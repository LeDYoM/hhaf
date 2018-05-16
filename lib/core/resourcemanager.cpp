#include "resourcemanager.hpp"
#include <lib/include/core/log.hpp>

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
			inline auto add(A& factory, ResourceManager::ResourceList<sptr<T>> &container, const str &id, const str &fileName)
			{
				auto resource(msptr<T>(factory.loadFromFile(fileName)));
				container.push_back(ResourceManager::NamedIndex<sptr<T>>(id,resource));
				return resource;
			}

		}

		ResourceManager::ResourceManager() : AppService{}
		{
		}

		ResourceManager::~ResourceManager() = default;

		sptr<scene::TTFont> ResourceManager::getFont(const str &rid, const str &fileName)
		{
			if (!fileName.empty()) {
				return add(backend::ttfontFactory(), m_fonts, rid, fileName);
			} else {
				auto iterator(std::find_if(m_fonts.begin(), m_fonts.end(),
					[rid](const auto &node) {return node.first == rid; })
				);
				return iterator == m_fonts.end() ? nullptr : (*iterator).second;
			}
		}
		sptr<scene::Texture> ResourceManager::getTexture(const str &rid, const str& fileName)
		{
			if (!fileName.empty()) {
				return add(backend::textureFactory(), m_textures, rid, fileName);
			} else {
				auto iterator(std::find_if(m_textures.begin(), m_textures.end(),
					[rid](const auto &node) {return node.first == rid; })
				);
				return iterator == m_textures.end() ? nullptr : (*iterator).second;
			}
		}
	}
}
