#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

#include <lib/draw/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace sf
{
	class Texture;
}

namespace lib
{
	namespace draw
	{
		class TextureV1 : public core::HasName
		{
		public:
			TextureV1(str name);
			TextureV1(const sf::Texture &texture);

			virtual ~TextureV1();

			bool loadFromFile(const str& filename);
			vector2du32 size() const;

			const sf::Texture *backEndTexture() const;
		private:
			class TexturePrivate;
			uptr<sf::Texture> m_texturePrivateOld;
			uptr<TexturePrivate> m_texturePrivate;
		};
	}
}

#endif
