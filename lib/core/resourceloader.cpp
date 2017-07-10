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
		ResourceLoader::ResourceLoader(ResourceManager&rm) : rManager{ rm } {}

		ResourceLoader::~ResourceLoader() = default;

		void ResourceLoader::addToTTFontLoadList(const str & fileName, const str&id, sptr<scene::TTFont> pFont)
		{
			m_fonts.emplace_back(ResourceIdentification<sptr<scene::TTFont>>{ fileName, { id, std::move(pFont) }});
		}

		void ResourceLoader::addToTextureLoadList(const str & fileName, const str&id, sptr<scene::Texture> pTexture)
		{
			m_textures.emplace_back(ResourceIdentification<sptr<scene::Texture>>{ fileName, { id, std::move(pTexture) }});
		}

	}
}
