#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
#include <lib/include/iresourceslist.hpp>
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class ResourceManager : public AppService, public Configuration
		{
		public:
			ResourceManager(const str &resourceFile);
			~ResourceManager();

			template <typename T>
			sptr<T> getResource(const str& rid) const;

			template <>
			sptr<scene::TTFont> getResource<scene::TTFont>(const str& rid) const
			{
				return getFont(rid);
			}

			template <>
			sptr<scene::Texture> getResource<scene::Texture>(const str& rid) const
			{
				return getTexture(rid);
			}

			sptr<scene::TTFont> getFont(const str &rid) const;
			sptr<scene::Texture> getTexture(const str &rid) const;

			///// New API
			u32 loadFontList(ResourceLoader &rLoader);
			u32 loadTextureList(ResourceLoader &rLoader);

			template <typename T>
			sptr<T> createResourceList() {
				IResourcesList *pResourceList(msptr<T>());
				ResourceLoader loader;
				pResourceList->registerResources(loader);
				loadFontList(loader.m_fonts);
				loadTextureList(loader.m_textures);
			}

		private:
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
		};
	}
}

#endif
