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
		ResourceLoader::ResourceLoader() = default;
		ResourceLoader::~ResourceLoader() = default;

		bool ResourceLoader::ensureLoad(ResourceManager &resourceManager)
		{
//			resourceManager.loadFontList(m_private->m_fonts);
//			resourceManager.loadTextureList(m_private->m_textures);
			return true;
		}

		void ResourceLoader::addToLoadList(const str & fileName)
		{
			m_fileNames.push_back(fileName);
		}

		sptr<scene::Texture> ResourceLoader::getLoadedResourceTexture(const str&fileName)
		{

		}

		sptr<scene::Texture> ResourceLoader::getLoadedResourceTTFont(const str&fileName)
		{

		}

	}
}
