#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
#include "appservice.hpp"
#include <list>

namespace lib
{
	class IResourcesList;
	class ResourceLoader;
	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		template <typename T>
		using NamedIndex = std::pair<const str, T>;

		template <typename T>
		using ResourceList = std::list<NamedIndex<T>>;

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
			u32 loadFontList(const string_vector &fileList);
			u32 loadTextureList(const string_vector &fileList);

			void registerResourceList(sptr<IResourcesList>);
			bool ensureLoaded(sptr<IResourcesList>);
		private:
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
			std::list<std::pair<sptr<ResourceLoader>,sptr<IResourcesList>>> m_resourceListList;
		};
	}
}

#endif
