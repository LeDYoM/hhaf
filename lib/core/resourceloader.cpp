#include "resourceloader.hpp"
#include <mtypes/include/log.hpp>
#include "resourcemanager.hpp"
#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>
#include <map>

namespace lib
{
	namespace core
	{
		struct ResourceLoader::ResourceLoaderPrivate
		{
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
		};
		ResourceLoader::ResourceLoader() : m_private{ muptr<ResourceLoaderPrivate>() } {}

		ResourceLoader::~ResourceLoader() = default;

		bool ResourceLoader::ensureLoad(ResourceManager &resourceManager)
		{
			resourceManager.loadFontList(m_private->m_fonts);
			resourceManager.loadTextureList(m_private->m_textures);
			return true;
		}

		void ResourceLoader::addToTTFontLoadList(const str & fileName, sptr<scene::TTFont> pFont)
		{
			m_private->m_fonts.emplace_back(fileName, std::move(pFont));
		}

		void ResourceLoader::addToTextureLoadList(const str & fileName, sptr<scene::Texture> pTexture)
		{
			m_private->m_textures.emplace_back(fileName, std::move(pTexture));
		}
	}
}
