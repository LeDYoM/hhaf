#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include "configuration.hpp"
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
		template <typename T>
		struct ResourceLoadStateNode
		{
			sptr<T> m_resource;
			str fileName;
		};
		using TTFontLoadStateNode = ResourceLoadStateNode<scene::TTFont>;
		using TextureLoadStateNode = ResourceLoadStateNode<scene::Texture>;

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

			template <typename T>
			using NamedIndex = std::pair<const str, T>;

			template <typename T>
			using ResourceList = std::list<NamedIndex<T>>;


			///// New API
			u32 loadFontList(const string_vector &fileList);
			u32 loadTextureList(const string_vector &fileList);

			bool addToLoadList(const str&fileName);
		private:

			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
		};
	}
}

#endif
