#pragma once

#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "iuserproperties.hpp"
#include "resourcemanager.hpp"

namespace lib
{
	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class ResourceLoader
		{
		public:
			ResourceLoader(str fileName);
			~ResourceLoader();

			template <typename T>
			inline void addToLoadList(const str&fileName, sptr<T>);

			template <>
			inline void addToLoadList(const str&fileName, sptr<scene::TTFont> pFont)
			{
				addToTTFontLoadList(fileName, std::move(pFont));
			}

			template <>
			inline void addToLoadList(const str&fileName, sptr<scene::Texture> pFont)
			{
				addToTextureLoadList(fileName, std::move(pFont));
			}

		private:
			void addToTTFontLoadList(const str&fileName, sptr<scene::TTFont> pFont);
			void addToTextureLoadList(const str&fileName, sptr<scene::Texture> pFont);

			struct ResourceLoaderPrivate;
			uptr<ResourceLoaderPrivate> m_private;
		};
	}
}

#endif
