#ifndef LIB_BACKEND_SFML_TEXTURETTFONT_INCLUDE_HPP__
#define LIB_BACKEND_SFML_TEXTURETTFONT_INCLUDE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <lib/backend/itexture.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace backend
	{
		class TextureTTFont : public ITexture
		{
		public:
			TextureTTFont(const sf::Texture &texture);
			virtual ~TextureTTFont();

			virtual vector2du32 size() const override;

			const sf::Texture &backEndTexture() const { return m_texturePrivate; }
		private:
			const sf::Texture &m_texturePrivate;
		};
	}
}

#endif
