#ifndef LIB_DRAW_TEXTURE_INCLUDE_HPP__
#define LIB_DRAW_TEXTURE_INCLUDE_HPP__

#include <SFML/Graphics/Texture.hpp>
#include <lib/draw/hasname.hpp>
#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>

namespace lib
{
	namespace draw
	{
		class Texture : public core::HasName
		{
		public:
			Texture(const std::string name);
			Texture(const sf::Texture &texture);

			bool loadFromFile(const std::string& filename);
			vector2du32 size() const;

			const sf::Texture *backEndTexture() const;
		private:
			class TexturePrivate;
			sf::Texture m_texturePrivate;
		};
	}
}

#endif
