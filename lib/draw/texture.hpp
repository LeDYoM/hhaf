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
		class Texture : public core::HasName
		{
		public:
			Texture(str_const name);
			Texture(const sf::Texture &texture);

			virtual ~Texture();

			bool loadFromFile(const std::string& filename);
			vector2du32 size() const;

			const sf::Texture *backEndTexture() const;
		private:
			class TexturePrivate;
			uptr<sf::Texture> m_texturePrivate;
		};
	}
}

#endif
