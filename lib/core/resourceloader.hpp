#pragma once

#ifndef LIB_RESOURCELOADER_INCLUDE_HPP__
#define LIB_RESOURCELOADER_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include "iuserproperties.hpp"

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
		class ResourceLoader final
		{
		public:
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
			ResourceLoader();
			~ResourceLoader();

			void addToTTFontLoadList(const str&fileName, sptr<scene::TTFont> pFont);
			void addToTextureLoadList(const str&fileName, sptr<scene::Texture> pFont);

			struct ResourceLoaderPrivate;
			uptr<ResourceLoaderPrivate> m_private;

			friend class ResourceManager;
		};
	}
}

#endif
