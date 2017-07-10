#pragma once

#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "iuserproperties.hpp"
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
		class ResourceManager;
		
		template <typename T>
		using NamedIndex = std::pair<const str, T>;

		template <typename T>
		using ResourceIdentification = std::pair<const str, NamedIndex<T>>;

		template <typename T>
		using ResourceList = std::list<NamedIndex<T>>;

		class ResourceLoader final
		{
		public:
			template <typename T>
			inline void addToLoadList(const str&fileName, const str&id, sptr<T>);

			template <>
			inline void addToLoadList(const str&fileName, const str&id, sptr<scene::TTFont> pFont)
			{
				addToTTFontLoadList(fileName, id, std::move(pFont));
			}

			template <>
			inline void addToLoadList(const str&fileName, const str&id, sptr<scene::Texture> pFont)
			{
				addToTextureLoadList(fileName, id, std::move(pFont));
			}

		private:
			ResourceLoader(ResourceManager&);
			~ResourceLoader();

			void addToTTFontLoadList(const str&fileName, const str&id, sptr<scene::TTFont> pFont);
			void addToTextureLoadList(const str&fileName, const str&id, sptr<scene::Texture> pTexture);
			std::list<ResourceIdentification<sptr<scene::TTFont>>> m_fonts;
			std::list<ResourceIdentification<sptr<scene::Texture>>> m_textures;

			friend class ResourceManager;
			ResourceManager &rManager;
		};
	}
}

#endif
