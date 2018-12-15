#pragma once

#ifndef LIB_SCENE_TEXTURE_INCLUDE_HPP
#define LIB_SCENE_TEXTURE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/vector2d.hpp>

namespace lib
{
	namespace backend
	{
		class ITexture;
	}
	namespace scene
	{
		class Texture final
		{
		public:
			Texture(backend::ITexture* texture);
			~Texture();

			vector2du32 size() const;

			const backend::ITexture* backEndTexture() const noexcept { return m_texturePrivate; }
		private:
			backend::ITexture *m_texturePrivate;
		};
	}
}

#endif
