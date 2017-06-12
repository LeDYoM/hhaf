#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

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
//			Texture();
			Texture(sptr<backend::ITexture> texture);
			~Texture();

			bool loadFromFile(const str& filename);
			vector2du32 size() const;

			const sptr<backend::ITexture> backEndTexture() const { return m_texturePrivate; }
		private:
			sptr<backend::ITexture> m_texturePrivate;
		};
	}
}

#endif
